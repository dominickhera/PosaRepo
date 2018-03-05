with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
procedure solveJumble is
-- delcare variables here
-- type stringArray is array (positive range <>) of character;
type anagramArray is array (positive range <>) of unbounded_string;
-- type dictionary is array (positive range <>) of stringArray;
type jumbleArray is array (1..1000) of unbounded_string;
type dictionary is array (positive range <>) of unbounded_string;
	

	function inputJumble return jumbleArray is
	jumbleList : jumbleArray;
	test : unbounded_string;
	-- word: string(1..1_000);
	length: integer;
	-- count: integer := 0;
	-- last: natural; 
	begin
		put("how many words do you want to add to the jumble?"); new_line;
		Ada.Integer_Text_IO.get(length);
		for i in 1..length+1 loop
			
			get_line(test);
			jumbleList(i) := test;
			put("\> ");
		end loop;
		return jumbleList;
		-- return word(1..last);
	end inputJumble;

	-- function generateAnagram(anagram: string(1..80)) return string is
	-- begin

	-- end generateAnagram
	function getFileLength return integer is
		fileLength : integer := 1;
		line : unbounded_string;
		infp : file_type;
	begin
		open(infp, in_file, "/usr/share/dict/words");
		-- open(infp, in_file, "/usr/share/dict/canadian-english-small");
		loop
			exit when end_of_file(infp);
			get_line(infp, line);
			fileLength := fileLength + 1;
		end loop;
		close(infp);
		return fileLength;
	end getFileLength;

	function buildLEXICON return dictionary is
		infp : file_type;
		k : integer := 1;
		fileLength : integer := getFileLength;
		-- line : string(1..80);
		line : unbounded_string;
		buildDictionary : dictionary(1..fileLength);
	begin
		-- buildDictionary := buildLEXICON;
		open(infp, in_file, "/usr/share/dict/words");
		-- open(infp, in_file, "/usr/share/dict/canadian-english-small");
		loop
			exit when end_of_file(infp);
			get_line(infp, line);
			-- put("line is: "); put(line); new_line;
			buildDictionary(k) := line;
			k := k + 1;
		end loop;
		-- put("file size is :");put(fileLength);new_line;
		k := 1;
		close(infp);

		return buildDictionary;
	end buildLEXICON;

	procedure swapChars(swapString: in out unbounded_string; charA: integer; charB: integer) is
		tempString: string := Ada.Strings.Unbounded.To_String(swapString);
		temp: string := tempString(charA..charA);
		A: string := tempString(charA..charA);
		B: string := tempString(charB..charB);
	begin

		-- A := B;
		-- B := temp;
		-- tempString(charA..charA) := A;
		-- tempString(charB..charB) := B;
		-- temp := Element(tempString, charA);
		-- A := Element(tempString, charA);
		-- B := Element(tempString, charB);
		-- temp := tempString(charA..charA);
		A := tempString(charA..charA);
		B := tempString(charB..charB);
		-- charA := charB;
		-- put("A is ");put(A);new_line;
		-- put("b is now ");put(B);new_line;
		tempString(charA..charA) := B;
		tempString(charB..charB) := temp;
		-- Element(tempString, charA) := B;
		-- Element(string, charB) := temp;
		put("new word is ");put(tempString);new_line;
		swapString := Ada.Strings.Unbounded.To_Unbounded_String(tempString);
		-- charB := temp;

	
	end swapChars;

	procedure anagramSearch(string: in out unbounded_string; beginNum: in out integer; endNum: in out integer) is
		intCount: integer := beginNum;
		endCount: integer := endNum;
		intTempNum: integer;
		intTempLength: integer;
		intSecondTempLength: integer;
		tempCharOne: unbounded_string;
		tempCharTwo: unbounded_string;
		tempCharThree: unbounded_string;
		tempCharFour: unbounded_string;
	begin
		for i in 1..length(string) loop
		-- loop
			-- exit when intCount = endCount;
			-- put(string); new_line;put("begin numb before swap is ");put(intCount);new_line;put("end count before swap is ");put(endCount);new_line;
			swapChars(string, beginNum, i);
			-- intTempLength:= string'size + beginNum;
			-- intSecondTempLength:= string'size + intCount;
			-- tempCharOne := Element(string, intCount);
			-- put(tempCharOne); new_line;
			-- tempCharTwo := Element(string, intSecondTempLength);
			-- swapChars(tempCharOne, tempCharTwo);
			if beginNum = endCount then
				intTempNum:= 0;
			else
				intTempNum:= beginNum + 1;
			end if;
			
			-- put(string); new_line;
			anagramSearch(string, intTempNum, endCount);

			swapChars(string, beginNum, endCount);
			-- intTempLength:= string'size + beginNum;
			-- intSecondTempLength:= string'size + intCount;
			-- tempCharThree := Element(string, intTempLength);
			-- tempCharFour := Element(string, intSecondTempLength);
			-- swapChars(tempCharThree, tempCharFour);
			-- intCount := intCount + 1;
		end loop;
	end anagramSearch;

	function findAnagram(anagramFind: in out anagramArray; dictionarySearch: in dictionary; jumbleSearch: in jumbleArray) return anagramArray is
		line: unbounded_string;
		beginNum: integer := 1;
		endNum: integer;
	begin
		for i in 2..jumbleSearch'length + 2 loop
			exit when jumbleSearch(i) = "";
			line := jumbleSearch(i);
			-- for k in 1..length(line) loop
				-- exit when Element(line, k) = "";
				-- endNum := endNum + 1;
			-- end loop;
			endNum := (length(line));
			anagramSearch(line, beginNum, endNum);
		end loop;


	return anagramFind;
	end findAnagram;




	-- length: integer;
	jumble : jumbleArray := inputJumble;
	wordDictionary : dictionary := buildLEXICON;
	anagramDictionary : anagramArray(1..10000);
	-- jumble : string(1..1_000);
	-- jumble : constant String := inputJumble;
	-- test: array (positive range <>) of character;
begin
	-- Put_Line("how many words do you want to enter?");
	-- Ada.Integer_Text_IO.get(length);
	for i in 2..jumble'length loop
		exit when jumble(i) = "";
		put("entered this jumble: "); put(jumble(i));new_line;
	end loop;

	anagramDictionary := findAnagram(anagramDictionary, wordDictionary, jumble);
	-- put("you entered this number: "); put(jumble(2)); new_line;
	-- jumble := inputJumble;
	-- jumble := inputJumble;
	-- Put_Line(jumble);
end solveJumble;