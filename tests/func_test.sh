echo
echo "DEBUT DE LA TESTSUITE"
echo


function test
{
	name="$1"
	command="$2"

	echo "# $name"

	../build/42sh -c "$command" > test_file.txt
	arg_test=$?
	env -i bash --posix -c "$command" > control_file.txt
	arg_control=$?

	diff -c test_file.txt control_file.txt
	result_argument=$?

	if [ $result_argument -ne 0 ]; then
		echo "   CORRIGE CA !!! Le test $name avec arguments passe PAS !!!"
		exit 1
	elif [ $arg_test -ne $arg_control ]; then
		echo "   CORRIGE CA !!! Le test $name avec arguments passe PAS !!! LES VALEURS DE RETOUR SONT DIFFERENTES"
		echo "return value de 42sh: $arg_test"
		echo "return value normal: $arg_control"
		exit 1
	fi


	echo "$command" > fichier.sh
	../build/42sh fichier.sh > test_file.txt
	file_test=$?
	env -i bash --posix fichier.sh > control_file.txt
	file_control=$?

	diff -c test_file.txt control_file.txt
	result_file=$?

	if [ $result_file -ne 0 ]; then
		echo "   CORRIGE CA !!! Le test $name avec file passe PAS !!!"
		exit 1
	elif [ $file_test -ne $file_control ]; then
		echo "   CORRIGE CA !!! Le test $name avec file passe PAS !!! LES VALEURS DE RETOUR SONT DIFFERENTES"
		echo "return value de 42sh: $file_test"
		echo "return value normal: $file_control"
		exit 1
	fi


	cat fichier.sh | ../build/42sh > test_file.txt
	input_test=$?
	cat fichier.sh | env -i bash --posix > control_file.txt
	input_control=$?

	diff -c test_file.txt control_file.txt
	result_input=$?

	if [ $result_input -ne 0 ]; then
		echo "   CORRIGE CA !!! Le test $name en input passe PAS !!!"
		exit 1
	elif [ $input_test -ne $input_control ]; then
		echo "   CORRIGE CA !!! Le test $name avec input passe PAS !!! LES VALEURS DE RETOUR SONT DIFFERENTES"
		echo "return value de 42sh: $input_test"
		echo "return value normal: $input_control"
		exit 1
	fi

	echo "   Le test $name passe :)"

	echo
}

function test_file
{

	echo "# $1"
	../build/42sh "$1" > test_file.txt
	file_test=$?
	env -i bash --posix "$1" > control_file.txt
	file_control=$?

	diff -c test_file.txt control_file.txt
	result_file=$?

	if [ $result_file -ne 0 ]; then
		echo "   CORRIGE CA !!! Le test "$1" avec file passe PAS !!!"
		exit 1
	elif [ $file_test -ne $file_control ]; then
		echo "   CORRIGE CA !!! Le test "$1" avec file passe PAS !!! LES VALEURS DE RETOUR SONT DIFFERENTES"
		echo "return value de 42sh: $file_test"
		echo "return value normal: $file_control"
		exit 1
	fi

	echo "   Le test "$1" passe :)"

	echo

}


test "Simple echo a" "echo a"

test "double echo" "echo a && echo b"

test "double echo fail on echo a" "ech a && echo b"

test "double echo fail on echo b" "echo a && ech b"

test "simple redirection >" " echo a >file"

test "simple redirection >|" " echo a >|file"

test "redirect error in file" "cd toto 2>file"

test "wrong redirect error" "cd toto 1>2"
rm 2

test "redirect input error" "echo a < b"

echo "in file" > file
test "redirect input " "cat <file"
rm file

test "redirection error" "1>&9"

test "redirection error 2" "2<&10"

test "redirection or" "(cd tbvirbvr || echo fonctionne) 1>>shell_redirection.txt;"

test "redirect error in file" "cd toto 2>essai.txt;"
rm essai.txt

test "echo in file" "echo toto >echo.txt;"

test "append in file" "echo append >>echo.txt;"

test "redirection overwrite" "echo overwritten >|echo.txt;"

test "redirection and" "(echo titi && echo un cd src/ qui fonctionne) 1>shell_redirection.txt;"

test "simple and" "echo a && echo b"

test "simple pipe" "echo toto | echo tata"

test "multiple pipe" "echo toto | echo tata | echo titi"

#test "pipe ls" "echo toto | ls"

for file in tests_if/*; do
	test_file "$file"
done

for file in tests_for/*; do
	test_file "$file"
done

for file in test_case/*; do
	test_file "$file"
done

test "simple case1" "case test in a* | t* ) echo le mot commence par un t ;; esac"
test "simple case2" "case atest in a* | t* ) echo le mot commence par un a ou t ;; esac"
test "simple case3" "case toto in a* ) echo ca ne doit pas marche ;;  t* ) echo le mot commence par un t ;;  l* ) echo ca ne doit pas marcher ;; esac"
test "simple case4" "case allo in a* ) echo le mot commence par a ;;  t* | u*) echo le mot commence par t ou u ;;  lynda ) echo le mot est lynda ;; esac"
test "simple case5" "case lynda in a* ) echo le mot commence par a ;;  t* | u*) echo le mot commence par t ou u ;;  lynda ) echo le mot est lynda ;; esac"
test "simple case6" "case ursula in a* ) echo le mot commence par a ;;  t* | u*) echo le mot commence par un t ou u ;;  lynda ) echo le mot est lynda ;; esac"
test "simple case7" "case dynastie in a* ) echo le mot commence par a ;;  t* | u*) echo le mot commence par t ou u ;;  lynda ) echo le mot est lynda ;; esac"
test "simple case8" "case toto in t* ) echo toto ;; esac"

for file in tests_function/*; do
	test_file "$file"
done


test "test while 1" " while break; do echo tata; done"

test "test while 2" "while echo tata; do break; done"

test "test while 3" "while echo tata && break; do echo pl; done"

test "test while 4" "while break || echo tata; do echo pl; done"

test "test while 5" "while break && echo tata; do echo pl; done"

test "test until 1" "until break; do echo tata; done"

test "test until 2" "until echo tata; do break; done"

test "test until 3" "until echo tata && break; do echo pl; done"

test "test until 4" "until break || echo tata; do echo zaa; done"

test "test until 5" "until break && echo tata; do echo zaa; done"

rm test_file.txt
rm control_file.txt

rm fichier.sh
