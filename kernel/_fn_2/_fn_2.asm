
_fn_2:     file format elf32-i386

Contents of section .text:
 400300 5589e583 ec0889c0 8945fc83 7d0c0074  U........E..}..t
 400310 73837d08 00746d83 7d100074 1183ec08  s.}..tm.}..t....
 400320 ff7510ff 750c8b45 08ffd083 c410837d  .u..u..E.......}
 400330 14007411 83ec08ff 7514ff75 0c8b4508  ..t.....u..u..E.
 400340 ffd083c4 10837d18 00741183 ec08ff75  ......}..t.....u
 400350 18ff750c 8b4508ff d083c410 837d1c00  ..u..E.......}..
 400360 741183ec 08ff751c ff750c8b 4508ffd0  t.....u..u..E...
 400370 83c41083 ec08ff75 fcff750c 8b4508ff  .......u..u..E..
 400380 d083c410 c9c3                        ......          
Contents of section .data:
Contents of section .comment:
 0000 00474343 3a202847 4e552920 332e322e  .GCC: (GNU) 3.2.
 0010 32203230 30333032 32322028 52656420  2 20030222 (Red 
 0020 48617420 4c696e75 7820332e 322e322d  Hat Linux 3.2.2-
 0030 352900                               5).             
Disassembly of section .text:

00400300 <_fn_2>:
  400300:	55                   	push   %ebp
  400301:	89 e5                	mov    %esp,%ebp
  400303:	83 ec 08             	sub    $0x8,%esp
  400306:	89 c0                	mov    %eax,%eax
  400308:	89 45 fc             	mov    %eax,0xfffffffc(%ebp)
  40030b:	83 7d 0c 00          	cmpl   $0x0,0xc(%ebp)
  40030f:	74 73                	je     400384 <_fn_2+0x84>
  400311:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
  400315:	74 6d                	je     400384 <_fn_2+0x84>
  400317:	83 7d 10 00          	cmpl   $0x0,0x10(%ebp)
  40031b:	74 11                	je     40032e <_fn_2+0x2e>
  40031d:	83 ec 08             	sub    $0x8,%esp
  400320:	ff 75 10             	pushl  0x10(%ebp)
  400323:	ff 75 0c             	pushl  0xc(%ebp)
  400326:	8b 45 08             	mov    0x8(%ebp),%eax
  400329:	ff d0                	call   *%eax
  40032b:	83 c4 10             	add    $0x10,%esp
  40032e:	83 7d 14 00          	cmpl   $0x0,0x14(%ebp)
  400332:	74 11                	je     400345 <_fn_2+0x45>
  400334:	83 ec 08             	sub    $0x8,%esp
  400337:	ff 75 14             	pushl  0x14(%ebp)
  40033a:	ff 75 0c             	pushl  0xc(%ebp)
  40033d:	8b 45 08             	mov    0x8(%ebp),%eax
  400340:	ff d0                	call   *%eax
  400342:	83 c4 10             	add    $0x10,%esp
  400345:	83 7d 18 00          	cmpl   $0x0,0x18(%ebp)
  400349:	74 11                	je     40035c <_fn_2+0x5c>
  40034b:	83 ec 08             	sub    $0x8,%esp
  40034e:	ff 75 18             	pushl  0x18(%ebp)
  400351:	ff 75 0c             	pushl  0xc(%ebp)
  400354:	8b 45 08             	mov    0x8(%ebp),%eax
  400357:	ff d0                	call   *%eax
  400359:	83 c4 10             	add    $0x10,%esp
  40035c:	83 7d 1c 00          	cmpl   $0x0,0x1c(%ebp)
  400360:	74 11                	je     400373 <_fn_2+0x73>
  400362:	83 ec 08             	sub    $0x8,%esp
  400365:	ff 75 1c             	pushl  0x1c(%ebp)
  400368:	ff 75 0c             	pushl  0xc(%ebp)
  40036b:	8b 45 08             	mov    0x8(%ebp),%eax
  40036e:	ff d0                	call   *%eax
  400370:	83 c4 10             	add    $0x10,%esp
  400373:	83 ec 08             	sub    $0x8,%esp
  400376:	ff 75 fc             	pushl  0xfffffffc(%ebp)
  400379:	ff 75 0c             	pushl  0xc(%ebp)
  40037c:	8b 45 08             	mov    0x8(%ebp),%eax
  40037f:	ff d0                	call   *%eax
  400381:	83 c4 10             	add    $0x10,%esp
  400384:	c9                   	leave  
  400385:	c3                   	ret    
Disassembly of section .data:
