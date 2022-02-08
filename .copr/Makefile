srpm:
	cp ../packages/fedora/kcm_webcam_settings.spec $(spec)
	dnf -y install tito
	tito init
	tito build --test --srpm --output=$(outdir)
	touch $(outdir)/`basename $(spec)`