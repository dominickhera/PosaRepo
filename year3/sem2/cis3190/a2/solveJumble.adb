with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
with Ada.Strings.Unbounded.Text_IO; use Ada.Strings.Unbounded.Text_IO;
procedure solveJumble is
-- delcare variables here
type stringArray is array (positive range <>) of character;
-- type dictionary is array (positive range <>) of stringArray;
type jumbleArray is array (1..1000) of unbounded_string;
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
		for i in 1..length loop
			get_line(test);
			jumbleList(i) := test;
			put("entered this jumble: "); put(jumbleList(i));new_line;

		end loop;
		-- put("entered this number: "); put(length);new_line;
		-- get_line(word, last);
		return jumbleList;
		-- return word(1..last);
	end inputJumble;

	-- function generateAnagram(anagram: string(1..80)) return string is
	-- begin

	-- end generateAnagram

	-- function buildLEXICON return dictionary is
	-- 	infp : file_type;
	-- 	i : integer := 0;
	-- 	line : string(1..80);
	-- 	buildDictionary : dictionary;
	-- begin
	-- 	buildDictionary := buildLEXICON;
	-- 	open(infp, in_file, "~/usr/share/dict/words");
	-- 	loop
	-- 		exit when end_of_file(infp);
	-- 		get(infp, line);
	-- 		buildDictionary(i) := line;
	-- 		i := i + 1;
	-- 	end loop;
	-- 	i := 0;
	-- 	close(infp);

	-- 	return dictionary;
	-- end buildLEXICON;

	-- procedure findAnagram is
	-- begin

	-- end findAnagram
	-- length: integer;
	jumble : jumbleArray := inputJumble;
	-- jumble : string(1..1_000);
	-- jumble : constant String := inputJumble;
	-- test: array (positive range <>) of character;
begin
	-- Put_Line("how many words do you want to enter?");
	-- Ada.Integer_Text_IO.get(length);
	put("you entered this number: "); put(jumble(1)); new_line;
	-- jumble := inputJumble;
	-- jumble := inputJumble;
	-- Put_Line(jumble);
end solveJumble;