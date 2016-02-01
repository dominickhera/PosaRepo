#!/usr/bin/perl
#
#   Packages and modules
#
use strict;
use warnings;
use version;   our $VERSION = qv('5.16.0');   # This is the version of Perl to be used
use Text::CSV  1.32;   # We will be using the CSV module (version 1.32 or higher)
# to parse each line

#
#   readFile.pl
#      Author(s): Matthew Falkner (0923667), Hugo Klepsch (0923883)
#      Project: Lab Assignment 1 Task 1 Script
#      Date of Last Update: Monday, November 16, 2015.
#
#      Functional Summary
#         readFile.pl takes in a CSV (comma separated version) file
#         and prints out the fields.
#         There are three fields:
#            1. name
#            2. gender (F or M)
#            3. number of people with this name
#
#         This code will also count the number of female and male
#         names in this file and print this out at the end.
#
#         The file represents the names of people in the population
#         for a particular year of birth in the United States of America.
#         Officially it is the "National Data on the relative frequency
#         of given names in the population of U.S. births where the individual
#         has a Social Security Number".
#
#      Commandline Parameters: 1
#         $ARGV[0] = name of the input file containing the names
#
#      References
#         Name files from http://www.ssa.gov/OACT/babynames/limits.html
#

#
#   Variables to be used
#
my $EMPTY = q{};
my $SPACE = q{ };
my $COMMA = q{,};


my $filenameYOB     = $EMPTY;
my $filenameCIS     = $EMPTY;

my @recordsYOB;
my @recordsCIS;
my @referencesCIS;

my @cisNames;
my $foundInd;
my $foundGenerIsFemaleOne;

my $record_countYOB = -1;
my $record_countCIS = -1;

my $maleInd;
my $switched = 0;

my $foundNames = 0;
my $missingNames = 0;
my $foundAName = 0;



my $female_count = 0;
my $male_count   = 0;
my @first_name;
my @gender;
my @number;
my $totalMale;
my $totalFemale;
my $csv          = Text::CSV->new({ sep_char => $COMMA });


#
#   Check that you have the right number of parameters
#

if ($#ARGV != 1) {
    print "Usage: findFirstName.pl yob1900.txt CIS2250Names.txt\n" or
    die "Print failure\n";
    exit;
} else {
    $filenameYOB = $ARGV[0];
    $filenameCIS = $ARGV[1];
}

#
#   Open the input file and load the contents into records array
#
open my $YOB_fh, '<', $filenameYOB
or die "Unable to open names file: file YOB1900 :)\n";
open my $CIS_fh, '<', $filenameCIS
or die "Unable to open names file: file CIS2500 NAMES :)\n";

@recordsYOB = <$YOB_fh>;
@recordsCIS = <$CIS_fh>;

close $YOB_fh or
die "Unable to close: $ARGV[0]\n";   # Close the input file
close $CIS_fh or
die "Unable to close: $ARGV[1]\n";

#
#   Parse each line and store the information in arrays
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
foreach my $name_recordYOB ( @recordsYOB ) {
    if ( $csv->parse($name_recordYOB) ) {
        my @master_fields = $csv->fields();
        $record_countYOB++;
        $first_name[$record_countYOB] = $master_fields[0];
        $gender[$record_countYOB]     = $master_fields[1];
        $number[$record_countYOB]     = $master_fields[2];
        if ($switched == 0 && $master_fields[1] eq "M") {
            $maleInd = $record_countYOB;
            $switched = 1;
        }
    } else {
        warn "Line/record could not be parsed: $recordsYOB[$record_countYOB]\n";
    }
}

foreach my $asdf ( @recordsCIS ) {
    if ( $csv->parse($asdf) ) {
        my @master_fields = $csv->fields();
        $record_countCIS++;
        $cisNames[$record_countCIS] = $master_fields[0];
        warn "Line/record could not be parsed: $recordsYOB[$record_countYOB]\n";
    }
}


for my $sweg (0 .. $record_countCIS) {
    $referencesCIS[$sweg] = 0;
}

for my $j (0..$#cisNames)
{
    $foundAName = 0;
    OUTER: for my $i ( 0..$#first_name)
   	{
        if ($first_name[$i] eq $cisNames[$j]) 
        {

                        
            $foundNames++;
            $foundAName = 1;
            for my $k ($i + 1 .. $#first_name){
                if ($cisNames[$j] eq $first_name[$k]) {
                    print $cisNames[$j] . " (" . ($i + 1) . ", " . ($k - $maleInd + 1) . ")\n";
                    last OUTER;
                }
            }
            if ($gender[$i] eq "F") {
                print $cisNames[$j] . " (" . ($i + 1).")\n"; 
            } else {
                print $cisNames[$j] . " (" . (($i) - $maleInd +1)  .")\n"; 
            }
            last;
           
       } 
        
   	}
    if ($foundAName == 1) {

        } else {
            print $cisNames[$j] . " (0)\n";
            $missingNames++;
        }
}

print "Number of found names: " . ($foundNames ) . "\n";
print "Number of missing names: $missingNames\n";

#
#   End of Scriptsssss
#
