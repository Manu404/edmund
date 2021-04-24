rm -rf ./bin

curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh

platform='unknown'
unamestr=`uname -o`
if [[ "$unamestr" == 'Msys' ]]; then
   platform='ms'
elif [[ "$unamestr" == 'GNU/Linux' ]]; then
   platform='linux'
fi

if [[ $platform == 'ms' ]]; then
	ln -s ./bin/arduino-cli.exe ./abn
elif [[ $platform == 'linux' ]]; then
	ln -s ./bin/arduino-cli ./abn
fi

./abn core update-index
