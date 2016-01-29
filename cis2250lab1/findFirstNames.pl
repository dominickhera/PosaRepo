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
#      readtopNames.pl
#      Author(s): Dominick Hera (0943778), Kevin Pirabaharan (0946212)
#      Project: Lab Assignment 1 Task 2 Script (Iteration 0)
#      Date of Last Update: Monday, January 18, 2016.
#
#      Functional Summary
#         readtopNames.pl takes in a CSV (comma separated version) file
#         and an integer which determines the size of the top names list.
#         it then prints out the top X (user inputted #) names of each gender
#         and the amount of people with said names in addition to a total count.
#         There are three fields:
#            1. name
#            2. gender (F or M)
#            3. number of people with this name
#
#         This code will also count the number of the top X females and males
#         in lists and print out the total number of people in America with
#         said names at the end of the lists.
#
#         The file represents the names of people in the population
#         for a particular year of birth in the United States of America.
#         Officially it is the "National Data on the relative frequency
#         of given names in the population of U.S. births where the individual
#         has a Social Security Number".
#
#      Commandline Parameters: 1
#         $ARGV[0] = name of the input file containing the names
#         $ARGV[1] = integer determing how many names per gender are shown
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

my $filename     = $EMPTY;
my $complist	 = $EMPTY;
my @records;
my @class_records;
my $record_count = -1;
my $class_record_count = -1;
my $total_count = 0;
my $top_class_count= 0;
my $class_miscount = 0;
my $top_fem_count = 0;
my $top_male_count= 0;
my $female_count = 0;
my $male_count   = 0;
my @first_name;
my @class_first_name;
my @class_number;
my @gender;
my @number;
my $csv          = Text::CSV->new({ sep_char => $COMMA });

#
#   Check that you have the right number of parameters
#
if ($#ARGV != 1 ) {
   print "Usage: readFile.pl <names file>\n" or
      die "Print failure\n";
   exit;
} else {
   $filename = $ARGV[0];
   $complist = $ARGV[1];
}

#
#   Open the input file and load the contents into records array
#
open my $names_fh, '<', $filename
   or die "Unable to open names file: $filename\n";

@records = <$names_fh>;

open my $class_names_fh, '<', $complist
   or die "Unable to open names file: $complist\n";

@class_records = <$class_names_fh>;

close $names_fh or
   die "Unable to close: $ARGV[0]\n";   # Close the input file

close $class_names_fh or
   die "Unable to close: $ARGV[1]\n";   # Close the input file

#
#   Parse each line and store the information in arrays
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
foreach my $class_name_record ( @class_records ) {
   if ( $csv->parse($class_name_record) ) {
      my @master_fields = $csv->fields();
      $class_record_count++;
      $class_first_name[$class_record_count] = $master_fields[0];
      $class_number[$class_record_count] = $master_fields[1];
   } else {
      warn "Line/record could not be parsed: $class_records[$class_record_count]\n";
   }
}

chomp(@class_records);

foreach my $name_record ( @records ) {
   if ( $csv->parse($name_record) ) {
      my @master_fields = $csv->fields();
      $record_count++;
      $first_name[$record_count] = $master_fields[0];
      $gender[$record_count]     = $master_fields[1];
      $number[$record_count]     = $master_fields[2];
   } else {
      warn "Line/record could not be parsed: $records[$record_count]\n";
   }
}
#
#   Print out the records and counts for females
#

for my $i ( 0..$class_record_count ) {
    for my $j ( 0..$record_count ) {
	if ($first_name[$j] eq $class_records[$i]) {
	  #  if ($number[$j] = $class_number[$i]) {
		if ($top_class_count < 72) { 
		$top_class_count++;
		print $class_records[$i].$SPACE."(".$number[$i].")\n" or
	            die "Print failure\n"
	} else {
	    $class_miscount++;
	    print $class_records[$i].$SPACE."(0)\n" or
		die "Print failure\n"	  
	   
	 # }	
	}
    }
   }
}
print 'Number of found names: '.$top_class_count."\n";
print 'Number of missing names: '.$class_miscount."\n";

#for my $i ( 0..$record_count ) {
#   if ( $gender[$i] eq 'F' ) {
#       if ( $top_fem_count < 10) {
#       print $first_name[$i].$SPACE."(".$number[$i].")\n" or
#          die "Print failure\n";
#      $top_fem_count++;
#      $female_count = $female_count + $number[$i];
#       }
#   }
#}
#print 'Total number of females: '.$female_count."\n";

#
#   Print out the records and counts for males
#
#for my $i ( 0..$record_count ) {
#    if ( $gender[$i] eq 'M' ) {
#       if ( $top_male_count < 10) {
#       print $first_name[$i].$SPACE."(".$number[$i].")\n" or
#          die "Print failure\n";
#       $top_male_count++;
#       $male_count = $male_count + $number[$i];
#        }
#    }
#}
#print 'Total number of males: '.$male_count."\n";

#$total_count = $female_count + $male_count;
#
#   Print out the records and counts for total
#
#print 'Total number: '.$total_count."\n" or
#   die "Print failure\n";

#
#   End of Script
#

