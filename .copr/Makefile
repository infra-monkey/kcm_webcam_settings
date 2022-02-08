srpm:
	cd dist/fedora
	dnf -y install tito
	tito init
	tito build --test --srpm --output=$(outdir)
	touch $(outdir)/`basename $(spec)`