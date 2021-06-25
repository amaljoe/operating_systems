if [ $# == 3 ]
then
    a=$1
    b=$2
else
    echo "Enter first number:"
    read a
    echo "Enter second number:"
    read b
fi
stop=false
# prompt the user untill he enters a correct option
while [ $stop != true ]
do
    echo "\nEnter your option (a- add, s- subtract, m -multiply, d- division):"
    read o
    stop=true
    case $o in
        a) echo "Sum after addition: " `expr $a + $b`;;
        s) echo "Difference after subtracttion: " `expr $a - $b`;;
        m) echo "Product after multiplication: " `expr $a \* $b`;;
        d) echo "Quotient after division: " `expr $a / $b` "     Reminder: " `expr $a % $b`;;
        *) echo "Wrong option, try again!!"
        stop=false;;
    esac
done