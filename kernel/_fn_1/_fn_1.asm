
_fn_1:     file format elf32-i386

Contents of section .text:
 400300 5589e583 ec08c745 fc000000 0083ec0c  U......E........
 400310 6a308b45 10ffd083 c410c745 f80a0000  j0.E.......E....
 400320 00817df8 ff000000 7602eb17 83ec086a  ..}.....v......j
 400330 00ff75f8 8b4514ff d083c410 8d45f8ff  ..u..E.......E..
 400340 00ebde83 ec0c6a31 8b4510ff d083c410  ......j1.E......
 400350 c745f80a 00000081 7df8ff00 00007602  .E......}.....v.
 400360 eb1783ec 086a0aff 75f88b45 14ffd083  .....j..u..E....
 400370 c4108d45 f8ff00eb de83ec0c 6a328b45  ...E........j2.E
 400380 10ffd083 c410c745 f80a0000 00817df8  .......E......}.
 400390 ff000000 7602eb17 83ec086a 14ff75f8  ....v......j..u.
 4003a0 8b4514ff d083c410 8d45f8ff 00ebde83  .E.......E......
 4003b0 ec0c6a33 8b4510ff d083c410 c745f80a  ..j3.E.......E..
 4003c0 00000081 7df8ff00 00007602 eb1783ec  ....}.....v.....
 4003d0 086a1eff 75f88b45 14ffd083 c4108d45  .j..u..E.......E
 4003e0 f8ff00eb de83ec0c 6a348b45 10ffd083  ........j4.E....
 4003f0 c410c745 f80a0000 00817df8 ff000000  ...E......}.....
 400400 7602eb17 83ec086a 28ff75f8 8b4514ff  v......j(.u..E..
 400410 d083c410 8d45f8ff 00ebde83 ec0c6a35  .....E........j5
 400420 8b4510ff d083c410 c745f80a 00000081  .E.......E......
 400430 7df8ff00 00007602 eb1783ec 086a32ff  }.....v......j2.
 400440 75f88b45 14ffd083 c4108d45 f8ff00eb  u..E.......E....
 400450 de83ec0c 6a368b45 10ffd083 c410c745  ....j6.E.......E
 400460 f80a0000 00817df8 ff000000 7602eb17  ......}.....v...
 400470 83ec086a 3cff75f8 8b4514ff d083c410  ...j<.u..E......
 400480 8d45f8ff 00ebde83 ec0c6a37 8b4510ff  .E........j7.E..
 400490 d083c410 c745f80a 00000081 7df8ff00  .....E......}...
 4004a0 00007602 eb1783ec 086a46ff 75f88b45  ..v......jF.u..E
 4004b0 14ffd083 c4108d45 f8ff00eb dec9c3    .......E....... 
Contents of section .data:
Contents of section .comment:
 0000 00474343 3a202847 4e552920 332e322e  .GCC: (GNU) 3.2.
 0010 32203230 30333032 32322028 52656420  2 20030222 (Red 
 0020 48617420 4c696e75 7820332e 322e322d  Hat Linux 3.2.2-
 0030 352900                               5).             
Disassembly of section .text:

00400300 <_fn_1>:
  400300:	55                   	push   %ebp
  400301:	89 e5                	mov    %esp,%ebp
  400303:	83 ec 08             	sub    $0x8,%esp
  400306:	c7 45 fc 00 00 00 00 	movl   $0x0,0xfffffffc(%ebp)
  40030d:	83 ec 0c             	sub    $0xc,%esp
  400310:	6a 30                	push   $0x30
  400312:	8b 45 10             	mov    0x10(%ebp),%eax
  400315:	ff d0                	call   *%eax
  400317:	83 c4 10             	add    $0x10,%esp
  40031a:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  400321:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  400328:	76 02                	jbe    40032c <_fn_1+0x2c>
  40032a:	eb 17                	jmp    400343 <_fn_1+0x43>
  40032c:	83 ec 08             	sub    $0x8,%esp
  40032f:	6a 00                	push   $0x0
  400331:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  400334:	8b 45 14             	mov    0x14(%ebp),%eax
  400337:	ff d0                	call   *%eax
  400339:	83 c4 10             	add    $0x10,%esp
  40033c:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  40033f:	ff 00                	incl   (%eax)
  400341:	eb de                	jmp    400321 <_fn_1+0x21>
  400343:	83 ec 0c             	sub    $0xc,%esp
  400346:	6a 31                	push   $0x31
  400348:	8b 45 10             	mov    0x10(%ebp),%eax
  40034b:	ff d0                	call   *%eax
  40034d:	83 c4 10             	add    $0x10,%esp
  400350:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  400357:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  40035e:	76 02                	jbe    400362 <_fn_1+0x62>
  400360:	eb 17                	jmp    400379 <_fn_1+0x79>
  400362:	83 ec 08             	sub    $0x8,%esp
  400365:	6a 0a                	push   $0xa
  400367:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40036a:	8b 45 14             	mov    0x14(%ebp),%eax
  40036d:	ff d0                	call   *%eax
  40036f:	83 c4 10             	add    $0x10,%esp
  400372:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  400375:	ff 00                	incl   (%eax)
  400377:	eb de                	jmp    400357 <_fn_1+0x57>
  400379:	83 ec 0c             	sub    $0xc,%esp
  40037c:	6a 32                	push   $0x32
  40037e:	8b 45 10             	mov    0x10(%ebp),%eax
  400381:	ff d0                	call   *%eax
  400383:	83 c4 10             	add    $0x10,%esp
  400386:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  40038d:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  400394:	76 02                	jbe    400398 <_fn_1+0x98>
  400396:	eb 17                	jmp    4003af <_fn_1+0xaf>
  400398:	83 ec 08             	sub    $0x8,%esp
  40039b:	6a 14                	push   $0x14
  40039d:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  4003a0:	8b 45 14             	mov    0x14(%ebp),%eax
  4003a3:	ff d0                	call   *%eax
  4003a5:	83 c4 10             	add    $0x10,%esp
  4003a8:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  4003ab:	ff 00                	incl   (%eax)
  4003ad:	eb de                	jmp    40038d <_fn_1+0x8d>
  4003af:	83 ec 0c             	sub    $0xc,%esp
  4003b2:	6a 33                	push   $0x33
  4003b4:	8b 45 10             	mov    0x10(%ebp),%eax
  4003b7:	ff d0                	call   *%eax
  4003b9:	83 c4 10             	add    $0x10,%esp
  4003bc:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  4003c3:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  4003ca:	76 02                	jbe    4003ce <_fn_1+0xce>
  4003cc:	eb 17                	jmp    4003e5 <_fn_1+0xe5>
  4003ce:	83 ec 08             	sub    $0x8,%esp
  4003d1:	6a 1e                	push   $0x1e
  4003d3:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  4003d6:	8b 45 14             	mov    0x14(%ebp),%eax
  4003d9:	ff d0                	call   *%eax
  4003db:	83 c4 10             	add    $0x10,%esp
  4003de:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  4003e1:	ff 00                	incl   (%eax)
  4003e3:	eb de                	jmp    4003c3 <_fn_1+0xc3>
  4003e5:	83 ec 0c             	sub    $0xc,%esp
  4003e8:	6a 34                	push   $0x34
  4003ea:	8b 45 10             	mov    0x10(%ebp),%eax
  4003ed:	ff d0                	call   *%eax
  4003ef:	83 c4 10             	add    $0x10,%esp
  4003f2:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  4003f9:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  400400:	76 02                	jbe    400404 <_fn_1+0x104>
  400402:	eb 17                	jmp    40041b <_fn_1+0x11b>
  400404:	83 ec 08             	sub    $0x8,%esp
  400407:	6a 28                	push   $0x28
  400409:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40040c:	8b 45 14             	mov    0x14(%ebp),%eax
  40040f:	ff d0                	call   *%eax
  400411:	83 c4 10             	add    $0x10,%esp
  400414:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  400417:	ff 00                	incl   (%eax)
  400419:	eb de                	jmp    4003f9 <_fn_1+0xf9>
  40041b:	83 ec 0c             	sub    $0xc,%esp
  40041e:	6a 35                	push   $0x35
  400420:	8b 45 10             	mov    0x10(%ebp),%eax
  400423:	ff d0                	call   *%eax
  400425:	83 c4 10             	add    $0x10,%esp
  400428:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  40042f:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  400436:	76 02                	jbe    40043a <_fn_1+0x13a>
  400438:	eb 17                	jmp    400451 <_fn_1+0x151>
  40043a:	83 ec 08             	sub    $0x8,%esp
  40043d:	6a 32                	push   $0x32
  40043f:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  400442:	8b 45 14             	mov    0x14(%ebp),%eax
  400445:	ff d0                	call   *%eax
  400447:	83 c4 10             	add    $0x10,%esp
  40044a:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  40044d:	ff 00                	incl   (%eax)
  40044f:	eb de                	jmp    40042f <_fn_1+0x12f>
  400451:	83 ec 0c             	sub    $0xc,%esp
  400454:	6a 36                	push   $0x36
  400456:	8b 45 10             	mov    0x10(%ebp),%eax
  400459:	ff d0                	call   *%eax
  40045b:	83 c4 10             	add    $0x10,%esp
  40045e:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  400465:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  40046c:	76 02                	jbe    400470 <_fn_1+0x170>
  40046e:	eb 17                	jmp    400487 <_fn_1+0x187>
  400470:	83 ec 08             	sub    $0x8,%esp
  400473:	6a 3c                	push   $0x3c
  400475:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  400478:	8b 45 14             	mov    0x14(%ebp),%eax
  40047b:	ff d0                	call   *%eax
  40047d:	83 c4 10             	add    $0x10,%esp
  400480:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  400483:	ff 00                	incl   (%eax)
  400485:	eb de                	jmp    400465 <_fn_1+0x165>
  400487:	83 ec 0c             	sub    $0xc,%esp
  40048a:	6a 37                	push   $0x37
  40048c:	8b 45 10             	mov    0x10(%ebp),%eax
  40048f:	ff d0                	call   *%eax
  400491:	83 c4 10             	add    $0x10,%esp
  400494:	c7 45 f8 0a 00 00 00 	movl   $0xa,0xfffffff8(%ebp)
  40049b:	81 7d f8 ff 00 00 00 	cmpl   $0xff,0xfffffff8(%ebp)
  4004a2:	76 02                	jbe    4004a6 <_fn_1+0x1a6>
  4004a4:	eb 17                	jmp    4004bd <_fn_1+0x1bd>
  4004a6:	83 ec 08             	sub    $0x8,%esp
  4004a9:	6a 46                	push   $0x46
  4004ab:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  4004ae:	8b 45 14             	mov    0x14(%ebp),%eax
  4004b1:	ff d0                	call   *%eax
  4004b3:	83 c4 10             	add    $0x10,%esp
  4004b6:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  4004b9:	ff 00                	incl   (%eax)
  4004bb:	eb de                	jmp    40049b <_fn_1+0x19b>
  4004bd:	c9                   	leave  
  4004be:	c3                   	ret    
Disassembly of section .data:
