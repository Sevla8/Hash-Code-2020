# Loop over all the commits and use the --commit-filter
# to change only the email addresses

git filter-branch --commit-filter '

    # check to see if the committer (email is the desired one)
    if [ "$GIT_COMMITTER_EMAIL" = "dasilvaalvesb@gmail.com" ];
    then
            # Set the new desired name
            GIT_COMMITTER_NAME="Brandon ALVES BARBOSA";
            GIT_AUTHOR_NAME="Brandon ALVES BARBOSA";

            # Set the new desired email
            GIT_COMMITTER_EMAIL="brandon.alves.barbosa@gmail.com";
            GIT_AUTHOR_EMAIL="brandon.alves.barbosa@gmail.com";

            # (re) commit with the updated information
            git commit-tree "$@";
    else
            # No need to update so commit as is
            git commit-tree "$@";
    fi' 
HEAD
