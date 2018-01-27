with Ada.Text_IO; use Ada.Text_IO;
with Ada.Integer_Text_IO; use Ada.Integer_Text_IO;
with Ada.Float_Text_IO; use Ada.Float_Text_IO;
with Ada.Strings.Unbounded; use Ada.Strings.Unbounded;
procedure solveJumble is
-- delcare variables here
type stringArray is array (positive range <>) of character;
-- type dictionary is array (positive range <>) of stringArray;
type jumbleArray is array (positive range <>) of character;
	function inputJumble return string is
	word: string(1..1_000);
	last: natural; 
	begin
		get_line(word, last);
		return word(1..last);
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
	length: integer;
	jumble : string(1..1_000);
begin
	Put_Line("how many words do you wn");
	Ada.Integer_Text_IO.get(length);
	put("you entered this number: "); put(length); new_line;
	-- jumble := inputJumble;
	-- jumble := inputJumble;
	-- Put_Line(jumble);
end solveJumble;