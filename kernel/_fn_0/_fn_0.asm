
_fn_0:     file format elf32-i386

Contents of section .text:
 400300 5589e583 ec08c745 fc000000 00817dfc  U......E......}.
 400310 ffff0000 7602eb16 8b45fc05 00000a00  ....v....E......
 400320 c7000000 00008d45 fc830004 ebdf8b45  .......E.......E
 400330 08c70000 000a0083 ec0c6a06 8b450cff  ..........j..E..
 400340 d083c410 c745f800 00000081 7df8ff00  .....E......}...
 400350 00007602 eb2683ec 0cff75f8 8b4510ff  ..v..&....u..E..
 400360 d083c410 83ec08ff 75f8ff75 f88b4514  ........u..u..E.
 400370 ffd083c4 108d45f8 ff00ebcf c9c3      ......E.......  
Contents of section .data:
Contents of section .comment:
 0000 00474343 3a202847 4e552920 332e322e  .GCC: (GNU) 3.2.
 0010 32203230 30333032 32322028 52656420  2 20030222 (Red 
 0020 48617420 4c696e75 7820332e 322e322d  Hat Linux 3.2.2-
 0030 352900                               5).             
Disassembly of section .text:

00400300 <_fn_0>:
  400300:	55                   	push   %ebp
  400301:	89 e5                	mov    %esp,%ebp
  400303:	83 ec 08             	sub    $0x8,%esp
  400306:	c7 45 fc 00 00 00 00 	movl   $0x0,0xfffffffc(%ebp)
  40030d:	81 7d fc ff ff 00 00 	cmpl   $0xffff,0xfffffffc(%ebp)
  400314:	76 02                	jbe    400318 <_fn_0+0x18>
  400316:	eb 16                	jmp    40032e <_fn_0+0x2e>
  400318:	8b 45 fc             	mov    0xfffffffc(%ebp),%eax
  40031b:	05 00 00 0a 00       	add    $0xa0000,%eax
  400320:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
  400326:	8d 45 fc             	lea    0xfffffffc(%ebp),%eax
  400329:	83 00 04             	addl   $0x4,(%eax)
  40032c:	eb df                	jmp    40030d <_fn_0+0xd>
  40032e:	8b 45 08             	mov    0x8(%ebp),%eax
  400331:	c7 00 00 00 0a 00    	movl   $0xa0000,(%eax)
  400337:	83 ec 0c             	sub    $0xc,%esp
  40033a:	6a 06                	push   $0x6
  40033c:	8b 45 0c             	mov    0xc(%ebp),%eax
  40033f:	ff d0                	call   *%eax
  400341:	83 c4 10             	add    $0x10,%esp
  400344:	c7 45 f8 00 00 00 00 	movl   $0x0,0xfffffff8(%ebp)
  40034b:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  400352:	76 02                	jbe    400356 <_fn_0+0x56>
  400354:	eb 26                	jmp    40037c <_fn_0+0x7c>
  400356:	83 ec 0c             	sub    $0xc,%esp
  400359:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40035c:	8b 45 10             	mov    0x10(%ebp),%eax
  40035f:	ff d0                	call   *%eax
  400361:	83 c4 10             	add    $0x10,%esp
  400364:	83 ec 08             	sub    $0x8,%esp
  400367:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40036a:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40036d:	8b 45 14             	mov    0x14(%ebp),%eax
  400370:	ff d0                	call   *%eax
  400372:	83 c4 10             	add    $0x10,%esp
  400375:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  400378:	ff 00                	incl   (%eax)
  40037a:	eb cf                	jmp    40034b <_fn_0+0x4b>
  40037c:	c9                   	leave  
  40037d:	c3                   	ret    
Disassembly of section .data:
