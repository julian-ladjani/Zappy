#!/bin/bash

if [ "$#" != 3 ]
  then
      echo "Usage: $0 Port AITeam GraphicTeam"
      exit
fi

cp ../zappy_server ./
cp ../zappy_ai ./

zappy_launch () {
    echo -e "Launch : $2 $1 -> \e[1m$4\e[0m"
    $2 $1
    if [ $? -eq $3 ]
    then
	echo -e "\e[32m\e[1mPASSED\e[0m"
    else
	echo -e "\e[31m\e[1mFAILED\e[0m"
    fi
}

zappy_diff () {
    echo -n "Launch : echo -e \"$2\""
    echo -e " | nc -C 127.0.0.1 $1 -> \e[1m$4\e[0m"
    echo -e "$2" | nc -C 127.0.0.1 $1 > .tmp
    if grep -q "$3" .tmp
    then
	echo -e "\e[32m\e[1mPASSED\e[0m"
    else
	echo -e "\e[31m\e[1mFAILED\e[0m"
    fi
    rm .tmp
}

title () {
    echo -ne "\n**"
    for (( i=0; i<${#1}; i++)); do
	echo -ne "*"
    done
    echo -ne   "**\n*" $1 "*\n**"
    for (( i=0; i<${#1}; i++)); do
	echo -ne "*"
    done
	echo -e "**\n"
}

title "AI PARSING"

zappy_launch  ""				"./zappy_ai" 84 "No arguments"
zappy_launch  "test"				"./zappy_ai" 84 "Invalid argument"
zappy_launch  "-n '$2' -h '127.0.0.1'"		"./zappy_ai" 84 "No port"
zappy_launch  "-p $1 -h '127.0.0.1'"		"./zappy_ai" 84 "No team"
zappy_launch  "-p $1 -n '$2'"			"./zappy_ai" 84 "No IP"
zappy_launch  "-p 99999 -n '$2' -h '127.0.0.1'"	"./zappy_ai" 84 "Invalid port"
zappy_launch  "-p $1 -n '' -h '127.0.0.1'"	"./zappy_ai" 84 "Invalid team"
zappy_launch  "-p $1 -n '$2' -h 'A.B.C.D'"	"./zappy_ai" 84 "Invalid IP"

title "SERVER PARSING"

zappy_launch  ""						"./zappy_server" 84 "No arguments"
zappy_launch  "test"						"./zappy_server" 84 "Invalid argument"
zappy_launch  "-x 100 -y 100 -n 'test' -c 5 -f 1"		"./zappy_server" 84 "No port"
zappy_launch  "-p $1 -y 100 -n 'test' -c 5 -f 1"		"./zappy_server" 84 "No width"
zappy_launch  "-p $1 -x 100 -n 'test' -c 5 -f 1"		"./zappy_server" 84 "No height"
zappy_launch  "-p $1 -x 100 -y 100 -c 5 -f 1"			"./zappy_server" 84 "No teams"
zappy_launch  "-p $1 -x 100 -y 100 -n 'test' -f 1"		"./zappy_server" 84 "No clientNb"

title "AI COMMAND ERROR"

zappy_diff $1 "$2\nCommand\n"		"ko" "Invalid command"
zappy_diff $1 "$2\nTake something\n"	"ko" "Invalid Set"
zappy_diff $1 "$2\nSet something\n"	"ko" "Invalid Take"

title "GRAPHIC COMMAND ERROR"

zappy_diff $1 "$3\ncommand\n"	"suc" "Invalid command"
zappy_diff $1 "$3\nbct -1 -1\n"	"sbp" "Invalid tile"
zappy_diff $1 "$3\nsst -1\n"	"sbp" "Invalid time unit"

title "AI COMMAND"

zappy_diff $1 "$2\n"			"WELCOME" "Welcome"
zappy_diff $1 "$2\nForward\n"		"ok" "Forward"
zappy_diff $1 "$2\nRight\n"		"ok" "Right"
zappy_diff $1 "$2\nLeft\n"		"ok" "Left"
zappy_diff $1 "$2\n\Look\n"		"[player" "Look"
zappy_diff $1 "$2\nInventory\n"		"[food" "Inventory"
zappy_diff $1 "$2\nBroadcast Test\n"	"ok" "Broadcast"

title "GRAPHIC COMMAND"

zappy_diff $1 "$3\nmsz\n"	"msz" "Map size"
zappy_diff $1 "$3\nbct 0 0\n"	"bct" "Tile content"
zappy_diff $1 "$3\nmct\n"	"bct" "Map content"
zappy_diff $1 "$3\ntna\n"	"tna" "Team names"
zappy_diff $1 "$3\nsgt\n"	"sgt" "Time unit"
zappy_diff $1 "$3\nsst 100\n"	"sst" "Time unit modification"