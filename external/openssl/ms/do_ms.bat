
perl util\mkfiles.pl >MINFO
perl util\mk1mf.pl no-asm debug VC-WIN32 >ms\nt.mak
perl util\mk1mf.pl dll no-asm debug VC-WIN32 >ms\ntdll.mak
perl util\mk1mf.pl no-asm debug VC-CE >ms\ce.mak
perl util\mk1mf.pl dll no-asm debug VC-CE >ms\cedll.mak

perl util\mkdef.pl 32 libeay > ms\libeay32.def
perl util\mkdef.pl 32 ssleay > ms\ssleay32.def
