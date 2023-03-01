* How developers contribute to liblog

It's pretty simple, just fork the
[liblog repository](https://git.alessandroiezzi.it/libs/c/log.git) make your
changes on a feature branch then make a `request-pull` using `-p` switch and
send me the output to me at: `aiezzi AT alessandroiezzi PERIOD it`.

Following an example.

	git clone https://git.alessandroiezzi.it/libs/c/log.git
	git remote add upstream https://git.alessandroiezzi.it/libs/c/log.git
	git remote set-url origin your-repository.git

Make a branch from `master`:

	git checkout -b awesome-feature

Make your changes. Be sure to push your work:

	git push -u origin awesome-feature

Then make a `request-pull`:

	git request-pull -p origin/master awesome-feature

Put the output on a separate file and send me that via email.

I'll wait for you!
