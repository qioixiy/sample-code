# git flow

## urls
- [git flow link1](http://www.cnblogs.com/cnblogsfans/p/5075073.html)

## Git Flow代码示例
a. 创建develop分支

git branch develop
git push -u origin develop    
b. 开始新Feature开发

git checkout -b some-feature develop
# Optionally, push branch to origin:
git push -u origin some-feature    

# 做一些改动    
git status
git add some-file
git commit    
c. 完成Feature

git pull origin develop
git checkout develop
git merge --no-ff some-feature
git push origin develop

git branch -d some-feature

# If you pushed branch to origin:
git push origin --delete some-feature    
d. 开始Relase

git checkout -b release-0.1.0 develop

# Optional: Bump version number, commit
# Prepare release, commit
e. 完成Release

git checkout master
git merge --no-ff release-0.1.0
git push

git checkout develop
git merge --no-ff release-0.1.0
git push

git branch -d release-0.1.0

# If you pushed branch to origin:
git push origin --delete release-0.1.0   


git tag -a v0.1.0 master
git push --tags
f. 开始Hotfix

git checkout -b hotfix-0.1.1 master    
g. 完成Hotfix

git checkout master
git merge --no-ff hotfix-0.1.1
git push


git checkout develop
git merge --no-ff hotfix-0.1.1
git push

git branch -d hotfix-0.1.1

git tag -a v0.1.1 master
git push --tags

---
## `git flow cmd`
> 初始化: git flow init
> 开始新Feature: git flow feature start MYFEATURE
> Publish一个Feature(也就是push到远程): git flow feature publish MYFEATURE
> 获取Publish的Feature: git flow feature pull origin MYFEATURE
> 完成一个Feature: git flow feature finish MYFEATURE
> 开始一个Release: git flow release start RELEASE [BASE]
> Publish一个Release: git flow release publish RELEASE
> 发布Release: git flow release finish RELEASE
> 别忘了git push --tags
> 开始一个Hotfix: git flow hotfix start VERSION [BASENAME]
> 发布一个Hotfix: git flow hotfix finish VERSION
