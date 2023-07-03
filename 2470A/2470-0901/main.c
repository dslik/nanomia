// ---------------------------------------------------------------------------------
// 2470A Gateway - Demo program
// ---------------------------------------------------------------------------------
// This example program allows gate signals from each of the four inputs to the
// corresponding output only if the channel button has been pressed and is
// illuminated. Demonstrates gate input, output and button control.
// ---------------------------------------------------------------------------------
// Source:  Own work (David Slik, https://github.com/dslik)
// License: CERN-OHL-S v2 (https://github.com/dslik/nanomia/blob/main/license.md)
// ---------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/i2c.h"
#include "hardware/sync.h"
#include "pico/sem.h"

#include "ws2812.pio.h"

// Constants
#define WS2812_2440A_FP 4             // Base GPIO for front panel LEDs

#define I2C_ADDR        0b00100000    // I2C address of the target
#define I2C_SDA_PIN     2             // GPIO line to use for SDA
#define I2C_SCL_PIN     3             // GPIO line to use for SCL

#define GATE_1_IN_GPIO  25
#define GATE_3_IN_GPIO  11
#define GATE_5_IN_GPIO  10
#define GATE_7_IN_GPIO  5

#define GATE_2_OUT_GPIO 29
#define GATE_4_OUT_GPIO 28
#define GATE_6_OUT_GPIO 27
#define GATE_8_OUT_GPIO 26

// Global variables
static struct semaphore wait_for_event;
volatile uint8_t led_value_current = 0x00;

volatile uint8_t button_value_current = 0x00;
volatile uint8_t button_value_change = 0;

volatile uint8_t gate_input_current = 0x00;
volatile uint8_t gate_input_change = 0;


volatile uint32_t count = 0;
volatile uint32_t duration = 0;

// ---------------------------------------------------------------------------------
// Sends a colour to a WS2812-compatible smart LED
// ---------------------------------------------------------------------------------
static inline void put_pixel(uint32_t pixel_grb) {
    pio_sm_put_blocking(pio1, 0, pixel_grb << 8u);
}

// ---------------------------------------------------------------------------------
// Converts an RGB value into a format suitable for a WS2812-compatible LED
// ---------------------------------------------------------------------------------
static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b) {
    return
            ((uint32_t) (r) << 8) |
            ((uint32_t) (g) << 16) |
            (uint32_t) (b);
}

// ---------------------------------------------------------------------------------
// Writes a value to an MPC23017 IO expander register over I2C
// ---------------------------------------------------------------------------------
int mcp23017_write_register(i2c_inst_t* i2c, uint8_t i2c_addr, uint8_t reg_addr, uint8_t reg_value)
{
    uint8_t txdata[2];
    int     rval = PICO_ERROR_NONE;

    txdata[0] = reg_addr;
    txdata[1] = reg_value;

    rval = i2c_write_blocking(i2c, i2c_addr, txdata, 2, false);

    return rval;
}

// ---------------------------------------------------------------------------------
// Reads a value from a MPC23017 IO expander register over I2C
// ---------------------------------------------------------------------------------
int mcp23017_read_register(i2c_inst_t* i2c, uint8_t i2c_addr, uint8_t reg_addr, uint8_t* reg_value)
{
    int rval = PICO_ERROR_NONE;

    rval = i2c_write_blocking(i2c, i2c_addr, &reg_addr, 1, true);

    if(rval >= 0)
    {
        rval = i2c_read_blocking(i2c, i2c_addr, reg_value, 1, false);
    }

    return rval;
}

// ---------------------------------------------------------------------------------
// Checks button and gate inputs. If changes detected, release a semaphore allowing
// the main program to process the changes. Run as a period timer.
//
// This could be done using interrupts, but since the IO expander needs to be polled
// (as there are not enough I/O lines on the board to have an interrupt line from
// the expander connected), might as well use polling for everything.
// ---------------------------------------------------------------------------------
static bool check_inputs(struct repeating_timer *t)
{
    count = count + 1;
    uint64_t start_time = to_us_since_boot(get_absolute_time());
    uint64_t end_time = 0;

    uint8_t button_values = 0;
    uint8_t gate_values = 0;
    uint8_t event_detected = false;

    button_value_change = false;
    gate_input_change = false;

   // Check for button presses
    mcp23017_read_register(i2c1, I2C_ADDR, 0x13, &button_values);
    button_values = button_values ^ 0xFF;

    if(button_values != button_value_current)
    {
        button_value_current = button_values;
        button_value_change = true;
        event_detected = true;
    }

    // Check for gate input changes
    gate_values = gate_values + (gpio_get(GATE_1_IN_GPIO) * 1);
    gate_values = gate_values + (gpio_get(GATE_3_IN_GPIO) * 2);
    gate_values = gate_values + (gpio_get(GATE_5_IN_GPIO) * 4);
    gate_values = gate_values + (gpio_get(GATE_7_IN_GPIO) * 8);
    gate_values = gate_values ^ 0x0F;

    if(gate_values != gate_input_current)
    {
        gate_input_current = gate_values;
        gate_input_change = true;
        event_detected = true;
    }

    // Signal an event
    if(event_detected == true)
    {
        sem_release(&wait_for_event);
    }

    count = count + 1;
    end_time = to_us_since_boot(get_absolute_time());
    duration = end_time - start_time;

}

// ---------------------------------------------------------------------------------
// Turns on and off the button LEDs using the IO expander
// ---------------------------------------------------------------------------------
void update_button_leds(uint8_t led_value_new)
{
    uint8_t value = 0;

    led_value_current = led_value_new;

    if(led_value_current & 0x02)
    {
        value = value | 0b00000011;
    }

    if(led_value_current & 0x01)
    {
        value = value | 0b00001100;
    }

    if(led_value_current & 0x04)
    {
        value = value | 0b00110000;
    }

    if(led_value_current & 0x08)
    {
        value = value | 0b11000000;
    }

    mcp23017_write_register(i2c1, I2C_ADDR, 0x12, value);
}

// ---------------------------------------------------------------------------------
// Turns on and off gate outputs using RP2040 GPIOs
// ---------------------------------------------------------------------------------
void set_gates(uint8_t gate_values)
{
    // Gate outputs are high when GPIO is low, so need to invert
    gpio_put(GATE_2_OUT_GPIO, (gate_values & 0x01) == 0);
    gpio_put(GATE_4_OUT_GPIO, (gate_values & 0x02) == 0);
    gpio_put(GATE_6_OUT_GPIO, (gate_values & 0x04) == 0);
    gpio_put(GATE_8_OUT_GPIO, (gate_values & 0x08) == 0);
}


// ---------------------------------------------------------------------------------
// Main program
// Initializes subsystems, then in an infinite loop, handles events to only
// allow gate inputs to the corresponding output if the corresponding button
// is enabled and illuminated.
// ---------------------------------------------------------------------------------
int main() {
    struct  repeating_timer scan_timer;

    stdio_init_all();

    printf("\n\n");
    printf("---------------------------------------------------------------------------------\n");
    printf("Nanomia 2470A Gateway Eurorack Module, Firmware 0.1.0-alpha.2\n");
    printf("CERN-OHL-S v2 (https://github.com/dslik/nanomia/blob/main/license.md)\n");
    printf("---------------------------------------------------------------------------------\n");
    
    // =======================================
    printf("Gate input init...\n");

    gpio_init(GATE_1_IN_GPIO);
    gpio_set_dir(GATE_1_IN_GPIO, GPIO_IN);

    gpio_init(GATE_3_IN_GPIO);
    gpio_set_dir(GATE_3_IN_GPIO, GPIO_IN);

    gpio_init(GATE_5_IN_GPIO);
    gpio_set_dir(GATE_5_IN_GPIO, GPIO_IN);

    gpio_init(GATE_7_IN_GPIO);
    gpio_set_dir(GATE_7_IN_GPIO, GPIO_IN);

    // =======================================
    printf("Gate output init...\n");

    gpio_init(GATE_2_OUT_GPIO);
    gpio_set_dir(GATE_2_OUT_GPIO, GPIO_OUT);
    gpio_put(GATE_2_OUT_GPIO, 1);

    gpio_init(GATE_4_OUT_GPIO);
    gpio_set_dir(GATE_4_OUT_GPIO, GPIO_OUT);
    gpio_put(GATE_4_OUT_GPIO, 1);

    gpio_init(GATE_6_OUT_GPIO);
    gpio_set_dir(GATE_6_OUT_GPIO, GPIO_OUT);
    gpio_put(GATE_6_OUT_GPIO, 1);

    gpio_init(GATE_8_OUT_GPIO);
    gpio_set_dir(GATE_8_OUT_GPIO, GPIO_OUT);
    gpio_put(GATE_8_OUT_GPIO, 1);

    // =======================================
    printf("PIO init...\n");

    // Choose PIO instance (0 or 1)
    PIO pio = pio1;

    // Get first free state machine in PIO 1
    uint sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &ws2812_program);

    // Turn off all front panel LEDs
    ws2812_program_init(pio, sm, offset, WS2812_2440A_FP, 800000, false);

    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));
    put_pixel(urgb_u32(0,0,0));

    // =======================================
    printf("I2C init...\n");

    // Initialize the i2c subsystem
    sleep_ms(10);

    gpio_pull_up(I2C_SDA_PIN);
    gpio_pull_up(I2C_SCL_PIN);
    gpio_set_function(I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL_PIN, GPIO_FUNC_I2C);
    i2c_init(i2c1, 100 * 1000);

    int ret = PICO_ERROR_NONE;
    uint8_t rxdata1 = 0xA3;

    ret = mcp23017_read_register(i2c1, I2C_ADDR, 0x00, &rxdata1);

    if(ret < 0)
    {
        printf("   ERROR: Unable to initialize I2C connection. Ret: %i Val: 0x%X\n", ret, rxdata1);
        put_pixel(urgb_u32(10,0,00));
    }

    // Set all GPIO A I/O lines to be outputs
    ret = mcp23017_write_register(i2c1, I2C_ADDR, 0x00, 0b00000000);

    // Set all GPIO A I/O lines to zero
    ret = mcp23017_write_register(i2c1, I2C_ADDR, 0x12, 0b00000000);

    // Set all GPIO B I/O lines to be inputs
    ret = mcp23017_write_register(i2c1, I2C_ADDR, 0x01, 0b11111111);

    // Enable all GPIO B I/O line pull-up Resistors
    ret = mcp23017_write_register(i2c1, I2C_ADDR, 0x0D, 0b11111111);

    // Initialize the event semaphore
    sem_init(&wait_for_event, 1, 1);
    add_repeating_timer_us(500, check_inputs, NULL, &scan_timer);

    // =======================================
    printf("Setting Front Panel LEDs to Gate...\n");
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(20,12,14));
    put_pixel(urgb_u32(0,0,0));

    // =======================================
    printf("Running program.\n");
    while(true)
    {
        if(sem_acquire_timeout_ms(&wait_for_event, 100))
        {
            if(button_value_change)
            {
                update_button_leds(led_value_current ^ button_value_current);
            }

            set_gates(led_value_current & gate_input_current);

            //printf("Gate Status - Change: %i Val: 0x%X\n", gate_input_change, gate_input_current);
            //printf("Button Status - Change: %i Val: 0x%X\n", button_value_change, button_value_current);
            //printf("Gate Output: 0x%X\n", led_value_current & gate_input_current);            
        }
    }
}
