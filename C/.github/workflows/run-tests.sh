cd ./C
make run-regressions filter=all
echo $?
echo "ASDADSASDASDADS:"
if [ $? -eq 1 ]
then
    exit 1
else
    exit 0
fi

cd -
