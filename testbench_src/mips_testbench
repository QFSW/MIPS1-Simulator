#!/bin/bash 

clear
dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"
srcPath="$dir/tests"
outDir="test"
outPath="$outDir/output.csv"
outTxt=""
simPath=$1
warnings=()
failures=()

run_test()
{
    binFile="$2"
    fileName=$(basename "$binFile")
    fileName="${fileName%%.*}"
    metaFile="${binFile%.*}.meta"
    testID=${fileName// /-}

    if [ -f "$metaFile" ]; then
        metaData=()
        while read -r line  || [[ -n "$line" ]]; do
            metaData+=("${line//#}")
        done < "$metaFile"
    
        testInstr=${metaData[0]}
        expectedReturn=${metaData[1]}
        author=${metaData[2]}
        extraInfo=${metaData[3]}
        
        "$simPath" "$binFile"
        return=$?
        if [ $return -ge 128 ]; then
            ((return-=256))
        fi

        message="exit code $return"
        
        if [ ! "$extraInfo" = "" ]; then
            message="$extraInfo; $message"
        fi

        if ((return == expectedReturn)); then
            status="Pass"
        else
            status="Fail"
            message+=" (expected $expectedReturn)"
            
            failure="test case '$testID' failed: $message"
            failures+=("$failure")

            echo "FAIL: $failure"
        fi

        outTxt="$outTxt$testID, $testInstr, $status, $author, $message\n"
    else
        warning="test case '$testID' did not have a corresponding .meta file and could not be performed"
        warnings+=("$warning")

        echo "WARNING: $warning"
    fi
}

binFiles="/$srcPath/*.bin";
for bin in $binFiles
do
    run_test "$1" "$bin"
done

mkdir -p $outDir
printf "$outTxt" > $outPath

warningCount=${#warnings[@]}
if [ $warningCount -ge 1 ]; then
    printf "\n\n$warningCount warnings were encountered\n" 
    for warning in "${warnings[@]}"
    do
        echo " - $warning"
    done
fi

failureCount=${#failures[@]}
if [ $failureCount -ge 1 ]; then
printf "\n\n$failureCount failures were encountered\n" 
for failure in "${failures[@]}"
    do
        echo " - $failure"
    done
fi

echo
