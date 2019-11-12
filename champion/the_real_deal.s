.name "the_real_deal"
.comment "this is the real deal..."

        sti r1, %:live, %1
        ld %0, r12
fork:
        live %1
        fork %:fork
		aff r1
live:
        live %1
        zjmp %:live
