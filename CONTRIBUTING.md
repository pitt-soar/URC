# Contributing

This is a simple guide for contributing to Pitt's University Rover Challenge. If you have any questions, please either contact Nick or Alex.

1. The main branch is protected, you can not directly push commits to this branch. The main branch is considered the most recent production-ready code.

2. To perform work, please create a new branch to push commits into.
    * The process should be: `git add .` -> `git commit -m "explain here"` -> `git push`

3. When you have finished and tested your code, make a pull request. You need one approval to merge any commits into the main branch.

4. After the merge, the branch must be deleted or archived.

## Commands

We would recommend using SSH to get git set up through Github. See this [guide](https://www.theserverside.com/blog/Coffee-Talk-Java-News-Stories-and-Opinions/GitHub-SSH-Key-Setup-Config-Ubuntu-Linux) on how to do it. Then clone with SSH on this repository.

`git clone <url>` Clones a repository into your local development envirnoment.  
`git branch` Check which you are on and see other branches (q to quit).  
`git fetch` Downloads commits, files, and refs from a remote repository into your local repository.  
`git pull` Fetch and download content from a remote repository and immediately update the local repository to match that content.  
`git checkout <branch>` Switches to a different branch.  
`git rebase <base>` [Git rebase](https://www.atlassian.com/git/tutorials/rewriting-history/git-rebase).  
`git add <files or .>` Saves changes to staging area.  
`git commit -m "explain commit here"` Commits changes to the *LOCAL* repository.  
`git push` Pushes commits to the branch on Github.  

## Other tips

1. Keep commit descriptions accurate and clear. Do not put descriptions like '.' or 'u'.
2. If you encounter problems, ask!
