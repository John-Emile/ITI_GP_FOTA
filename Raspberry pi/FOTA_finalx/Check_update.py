from pickle import TRUE
import pygit2
from github import Github
import os
def update ():


	g = Github('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')

	user = g.get_user()
	repos = user.get_repos()

	latest_commit = ''
	with open('checkUpdates.txt','r') as file:
		latest_commit = file.read()
	file.close()

	for repo in repos:
		# get the latest commit
		if(repo.name == 'Data_update'):
			if( repo.get_commits()[0].sha != latest_commit ):
				os.system(f"sudo rm -r {repo.name}")
				pygit2.clone_repository(url=repo.clone_url,path=f'{repo.name}')
				with open('checkUpdates.txt','w') as file:
					file.write(repo.get_commits()[0].sha)
				file.close()
				return True
			else:
				print("no update")
				return False

