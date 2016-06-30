@echo off
@pushd	%~dp0

@COPY	/Y	Release\*.exe		example\
@IF	NOT	ERRORLEVEL		0			@PAUSE

@popd
@echo	on