#!/usr/bin/awk -f
BEGIN {
	REPO_URL = getRepoURL()
	# Prefixes that determine whether a commit will be printed
	#CHANGELOG_REGEX = "^(changelog|Update|fix|add|docs|chore|feat|feature|refactor|update||): "
	FS="|"
	# %D: tags
	# %s: commit message
	# %H: long hash
	# %h: short hash
	while ("git log --pretty='%D|%s|%H|%h'" | getline) {
		IS_GIT_TAG = length($1) && match($1, /tag:/)
		if (IS_GIT_TAG) {
			printTag($1)
		} else {
			printCommit($2, $3, $4)
		}

	}
}
function printTag(input) {
	# Cut out text up to tag
	sub(/.*tag: /, "", input)
	# Cut out text after tag
	sub(/,.*/, "", input)
	if (TYPE == "plain")
		printf("\n%s\n", input)
	else
		printf("\n## %s\n", input)
}
function printCommit(input, longHash, shortHash) {
	if ( match(input, CHANGELOG_REGEX) ) {
		sub(CHANGELOG_REGEX, "", input)
		if (TYPE == "plain")
			printf("\t- %s\n", input, makeCommitLink(REPO_URL, shortHash, longHash) )
		else
			printf("- %s (%s)\n", input, makeCommitLink(REPO_URL, shortHash, longHash) )
	}
}
function makeCommitLink(repoUrl, shortHash, longHash) {
	return ("[" shortHash "](https://github.com/i-nex/I-Nex/commit/" longHash ")")
}

# Get Git repo URL
function getRepoURL() {
	"git config --get remote.upstream.url || git config --get remote.origin.url || git config --get remote.dev.url" | getline REPO_URL
	sub(/:/, "/", REPO_URL)
	sub(/git@/, "https://", REPO_URL)
	sub(/\.git/, "", REPO_URL)
	return REPO_URL
}
