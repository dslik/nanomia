# Utility program to transform a CSV formatted waveform into a format that can be pasted
# into an EasyEDA PCB design.

input_file = File.read("waveform.csv")

lines = input_file.split("\n")
counter = 3000

lines.each do |line|
	items = line.split(", ")
	print "    \"TRACK~1~3~S$#{15 + counter}~#{(items[0].to_f/3.0 + 4000.0).round(3)} " +
											"#{(items[1].to_f/8.0 + 3200.0).round(3)} " + 
											"#{(items[2].to_f/3.0 + 4000.0).round(3)} " +
											"#{(items[3].to_f/8.0 + 3200.0).round(3)}~gge12~0\",\n"
	counter = counter + 1
end
