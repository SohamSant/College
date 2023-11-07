#!/bin/bash
# Create a directory named "DataBase" and move into it.
mkdir DataBase
cd DataBase
# Initialize the variable "ans" to 0.
ans=0
# Start an infinite loop to display the menu until the user chooses to exit (option 7).
while [ $ans -ne 7 ]; do
# Display the menu options.
echo -e "\n----------------------------"
echo "| ***MENU*** |"
echo "----------------------------"
echo "|1.Create Database |"
echo "|2.Display Database |"
echo "|3.Search Record |"
echo "|4.Insert Record |"
echo "|5.Delete Record |"
echo "|6.Modify Record |"
echo "|7.Exit |"
echo "----------------------------"
echo -n "Enter your choice => "
read ans
# Use the "case" statement to execute the corresponding block of code based on the user's choice.
case $ans in

1)
# Option 1: Create a new database.
echo -n "Name Your database => "
read name
touch "$db_name}.txt"
>"${db_name}.txt"
echo -n "Enter number of records => "
read total
i=0
uid=0
# Start a loop to input the records for the database.
while [ $i -lt $total ]; do
echo -n "Enter name of student $(( i + 1 )) => "
read name
echo -n "Enter age of $name => "
read age
echo -n "Enter phone number of $name => "
read phone
echo -n "Enter pointer of $name => "
read pointer
uid=$(( $uid + 1 ))
# Append the record to the database file.
echo "${uid}|${name}|${age}|${phone}|${pointer}|" >> "${db_name}.txt"
i=$(( $i + 1 ))
done
echo "Database Created"
;;
# Option 2: Display the contents of a database file.
2)
echo -n "Enter the name of the database to display => "
read db_name
if [ -f "${db_name}.txt" ]; then
cat "${db_name}.txt"
else
echo "Database not found!"
fi
;;
# Option 3: Search for a record in a database.
3)
echo -n "Enter the name of the database to search => "
read db_name
echo -n "Enter the name of the student to search => "
read search_name
if [ -f "${db_name}.txt" ]; then
grep -i "${search_name}" "${db_name}.txt"
else
echo "Database not found!"
fi
;;
# Option 4: Insert a new record into a database.
4)
echo -n "Enter the name of the database to insert record => "
read db_name

if [ -f "${db_name}.txt" ]; then
echo -n "Enter name of the student => "
read name
echo -n "Enter age of $name => "
read age
echo -n "Enter phone number of $name => "
read phone
echo -n "Enter pointer of $name => "
read pointer
uid=$(( $uid + 1 ))
# Append the new record to the database file.
echo "${uid}|${name}|${age}|${phone}|${pointer}|" >> "${db_name}.txt"
echo "Record Inserted"
else
echo "Database not found!"
fi
;;
# Option 5: Delete a record from a database.
5)
echo -n "Enter the name of the database to delete record => "
read db_name
if [ -f "${db_name}.txt" ]; then
echo -n "Enter the name of the student to delete => "
read delete_name
# Use grep to filter out the record to be deleted and create a temporary file.
grep -iv "${delete_name}" "${db_name}.txt" > "${db_name}_temp.txt"
# Rename the temporary file as the new database file, effectively deleting the record.
mv "${db_name}_temp.txt" "${db_name}.txt"
echo "Record Deleted"
else
echo "Database not found!"
fi
;;
# Option 6: Modify a record in a database.
6)
echo -n "Enter the name of the database to modify record => "
read db_name
if [ -f "${db_name}.txt" ]; then
echo -n "Enter the name of the student to modify => "
read modify_name
# Check if the record exists in the database.
if grep -iq "${modify_name}" "${db_name}.txt"; then
echo -n "Enter the attribute to modify (name, age, phone, pointer): "
read attribute
# Read the new value for the attribute.
echo -n "Enter the new value for ${attribute}: "
read new_value
# Update the attribute of the record using sed.
sed -i "s/\(^.*${modify_name}|.*|\).*\$/\1${new_value}|/" "${db_name}.txt"
echo "Record Modified"
else
echo "Record not found!"
fi
else
echo "Database not found!"

fi
;;
# Option 7: Exit the script.
7)
echo "BYE !!"
;;
# For any invalid input, display an error message.
*)
echo "Invalid choice. Please try again."
;;
esac
done
