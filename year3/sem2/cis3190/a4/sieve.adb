with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Calendar; use Ada.Calendar;

procedure sieve is

type sieveArray is array (positive range <>) of integer;

	function getLength return integer is
		length: integer;
	begin
		Put_Line("Enter the upper limit of prime numbers to calculate: ");
		Ada.Integer_Text_IO.get(length);
		return length;
	end getLength;

	beginTime: Time := Clock;
	endTime: Time;
	length: integer := getLength;
	intCheck : integer := 0;
	sieveArrayThing : sieveArray(2..length);
	outputFile : file_type;
begin

	for i in 2..length loop
		sieveArrayThing(i) := i;
	end loop;

	for i in 2..length loop
		if (sieveArrayThing(i) /= 0) then
			if (((2*(i + 1)) mod sieveArrayThing(i)) = 0) then
				intCheck := i * 2;
				for k in i..length loop
					if intCheck <= length then
						sieveArrayThing(intCheck) := 0;
						intCheck := k * 2;
					end if;
				end loop;
			end if;
		end if;
	end loop;

	for i in 2..length loop
		if (sieveArrayThing(i) /= 0) then
			if (((3*(i + 1)) mod sieveArrayThing(i)) = 0) then
				intCheck := i * 3;
				for k in i..length loop
					if intCheck <= length then
						sieveArrayThing(intCheck) := 0;
						intCheck := k * 3;
					end if;
				end loop;
			end if;
		end if;
	end loop;

	for i in 2..length loop
		if (sieveArrayThing(i) /= 0) then
			if (((5*(i + 1)) mod sieveArrayThing(i)) = 0) then
				intCheck := i * 5;
				for k in i..length loop
					if intCheck <= length then
						sieveArrayThing(intCheck) := 0;
						intCheck := k * 5;
					end if;
				end loop;
			end if;
		end if;
	end loop;

	create(outputFile, append_file, "primeNumberAdaOutput.txt");
	-- open(outputFile, append_file, "primeNumberAdaOutput.txt");
	put(outputFile, "results: ");new_line(outputFile);
	for i in 2..length loop
		if (sieveArrayThing(i) /= 0) then
			put(outputFile, sieveArrayThing(i));new_line(outputFile);
		end if;
	end loop;
	-- if is_open(outputFile) then
		-- close(outputFile);
	-- end if;
	endTime := Clock;
	put("Execution Time: ");put(Duration'Image(endTime - beginTime));put(" Seconds");new_line;
	
end sieve;