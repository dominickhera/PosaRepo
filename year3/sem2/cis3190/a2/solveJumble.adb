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
			put("\> ");
			get_line(test);
			jumbleList(i) := test;
			
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

	procedure findAnagram(anagramFind: in out anagramArray; dictionarySearch: in dictionary; jumbleSearch: in jumbleArray) return jumbleArray is
	begin



	return anagramFind;
	end findAnagram;
	-- length: integer;
	jumble : jumbleArray := inputJumble;
	wordDictionary : dictionary := buildLEXICON;
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
	-- put("you entered this number: "); put(jumble(2)); new_line;
	-- jumble := inputJumble;
	-- jumble := inputJumble;
	-- Put_Line(jumble);
end solveJumble;