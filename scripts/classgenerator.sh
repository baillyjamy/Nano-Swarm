echo "#include \""${1}.hpp"\"" >> source/${1}.cpp
echo "#ifndef "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> include/${1}.hpp
echo "# define "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> include/${1}.hpp
echo "" >> include/${1}.hpp
echo "class	"`echo ${1^}` >> include/${1}.hpp
echo "{" >> include/${1}.hpp
echo "public:" >> include/${1}.hpp
echo "};" >> include/${1}.hpp
echo "" >> include/${1}.hpp
echo "#endif // "`echo ${1} | tr [a-z] [A-Z]`"_HPP_" >> include/${1}.hpp
