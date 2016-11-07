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

#
#   Variables to be used
#
my $EMPTY = q{};
my $SPACE = q{ };
my $COMMA = q{,};

my $popFileName     = $EMPTY;
my @records;
my @classRecords;
my $record_count = -1;
my $class_record_count = -1;
my $female_count = 0;
my $male_count   = 0;
my $female_total = 0;
my $male_total = 0;
my @first_name;
my @class_first_name;
my @gender;
my @number;
my $csv          = Text::CSV->new({ sep_char => $COMMA });
my $i = 0;
my $temp = 0;
my $classFileName   = $EMPTY;
my $male = 0;
my $start = 0;
my $count;
my $count2;
my $numFound;
my $numNotFound;


#
#   Check that you have the right number of parameters
#
if ($#ARGV != 1 ) {
    print "Usage: readFile.pl <names file>\n" or
    die "Print failure\n";
    exit;
} else {
    $popFileName = $ARGV[0];
    $classFileName = $ARGV[1];
}

#
#   Open the input file and load the contents into records array
#
open my $names_fh, '<', $popFileName
or die "Unable to open names file: $popFileName\n";

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

open my $classs_fh, '<', $classFileName
or die "Unable to open names file: $classFileName\n";

@classRecords = <$classs_fh>;

close $classs_fh or
die "Unable to close: $ARGV[1]\n";   # Close the input file

#
#   Parse each line and store the information in arrays
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
foreach my $class_record ( @classRecords ) {
    if ( $csv->parse($class_record) ) {
        my @class_master_fields = $csv->fields();
        $class_record_count++;
        $class_first_name[$class_record_count] = $class_master_fields[0];
    } else {
        warn "Line/record could not be parsed: $records[$record_count]\n";
    }
}

#
#   Print out the records and counts

for (my $i = 0; $i<$record_count; $i++)
{
    if($gender[$i] eq 'F')
    {
        $start++;
    }
}

for ($i= 0; $i<$class_record_count+1; $i++)
{   $temp = 0;
    $count = 1;
    $count2 = 0;
    for (my $j = 0; $j<$record_count+1; $j++)
    {
        if ( $first_name[$j] eq $class_first_name[$i])
        {
            if ($first_name[$j] eq $class_first_name[$i] & $gender[$i] eq 'F' )
            {
                $count2 = 1;
                print $class_first_name[$j] . " (" . ($i + 1) . ", ". ($i - $record_count + 1) . ")\n";
            }
            if ($gender[$j] eq 'F')
            {
                print $class_first_name[$i].$SPACE.'('.($j+1).')'."\n" or
                    die "Print failure\n";
                $temp = 1;
                $count++;

            }
            else
            {
                if ($count== 1) {
                    $male = $j - ($start-1);
                    print $class_first_name[$i].$SPACE.'('.$male.')'."\n" or
                        die "Print failure\n";
                    $temp = 1;
                }
            }

        }

    }
    if ($temp != 1)
    {
        print $class_first_name[$i].$SPACE.'('.'0' .')'."\n" or
            die "Print failure\n";
        $count2 = 0;
        $numNotFound++;
    }
    if ($count2 == 1)
    {
        $numFound++;
    }

}
print "Number of found names: ". ($numFound)."\n" or
    die "Print failure\n";
print "Number of missing names: ". $numNotFound."\n" or
    die "Print failure\n";

#
#   End of Script
#
