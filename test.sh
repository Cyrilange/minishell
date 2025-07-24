new_entry="{
	"mtime" : "mymtime"
}"
jq --argjson new_entry "$new_entry" '. += [$new_entry]' compile_commands.json > temp.json && mv temp.json compile_commands.json
