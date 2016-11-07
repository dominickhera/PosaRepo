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
#      Author(s): Deborah Stacey
#      Project: Lab Assignment 1 Script (Iteration 0)
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

my $filename     = $EMPTY;
my @records;
my $record_count = -1;
my $female_count = 0;
my $male_count   = 0;
my $total_female_count = 0;
my $total_male_count = 0;
my @first_name;
my @gender;
my @number;
my $csv          = Text::CSV->new({ sep_char => $COMMA });

#
#   Check that you have the right number of parameters
#
if ($#ARGV != 0 ) {
   print "Usage: readFile.pl <names file>\n" or
      die "Print failure\n";
   exit;
} else {
   $filename = $ARGV[0];
}

#
#   Open the input file and load the contents into records array
#
open my $names_fh, '<', $filename
   or die "Unable to open names file: $filename\n";

@records = <$names_fh>;

close $names_fh or
   die "Unable to close: $ARGV[0]\n";   # Close the input file

#
#   Parse each line and store the information in arrays 
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
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
#   Print out the records and counts
#
for my $i ( 0..$record_count ) {
   print $first_name[$i].$SPACE.$gender[$i].$SPACE.$number[$i]."\n" or
      die "Print failure\n";
   if ( $gender[$i] eq 'F'  ) {
      $female_count++;
      $total_female_count = $total_female_count + $number[$record_count];
   } else {
      $male_count++;
      $total_male_count = $total_male_count + $number[$record_count];
   }
}
print 'Female Names: '.$female_count.', Total Females: '.$total_female_count.", Total Males: $total_male_count  and Male Names: '$male_count\n" or
   die "Print failure\n";

#
#   End of Script
#
