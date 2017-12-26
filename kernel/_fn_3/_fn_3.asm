
_fn_3:     file format elf32-i386

Contents of section .text:
 400300 5589e583 ec0883ec 0c6a008b 4510ffd0  U........j..E...
 400310 83c410c7 45fc0000 0000817d fc3f0100  ....E......}.?..
 400320 007e02eb 31c745f8 00000000 817df8ef  .~..1.E......}..
 400330 0000007e 02eb1883 ec08ff75 f8ff75fc  ...~.......u..u.
 400340 8b4514ff d083c410 8d45f8ff 00ebdd8d  .E.......E......
 400350 45fcff00 ebc4c9c3                    E.......        
Contents of section .data:
Contents of section .comment:
 0000 00474343 3a202847 4e552920 332e322e  .GCC: (GNU) 3.2.
 0010 32203230 30333032 32322028 52656420  2 20030222 (Red 
 0020 48617420 4c696e75 7820332e 322e322d  Hat Linux 3.2.2-
 0030 352900                               5).             
Disassembly of section .text:

00400300 <_fn_3>:
  400300:	55                   	push   %ebp
  400301:	89 e5                	mov    %esp,%ebp
  400303:	83 ec 08             	sub    $0x8,%esp
  400306:	83 ec 0c             	sub    $0xc,%esp
  400309:	6a 00                	push   $0x0
  40030b:	8b 45 10             	mov    0x10(%ebp),%eax
  40030e:	ff d0                	call   *%eax
  400310:	83 c4 10             	add    $0x10,%esp
  400313:	c7 45 fc 00 00 00 00 	movl   $0x0,0xfffffffc(%ebp)
  40031a:	81 7d fc 3f 01 00 00 	cmpl   $0x13f,0xfffffffc(%ebp)
  400321:	7e 02                	jle    400325 <_fn_3+0x25>
  400323:	eb 31                	jmp    400356 <_fn_3+0x56>
  400325:	c7 45 f8 00 00 00 00 	movl   $0x0,0xfffffff8(%ebp)
  40032c:	81 7d f8 ef 00 00 00 	cmpl   $0xef,0xfffffff8(%ebp)
  400333:	7e 02                	jle    400337 <_fn_3+0x37>
  400335:	eb 18                	jmp    40034f <_fn_3+0x4f>
  400337:	83 ec 08             	sub    $0x8,%esp
  40033a:	ff 75 f8             	pushl  0xfffffff8(%ebp)
  40033d:	ff 75 fc             	pushl  0xfffffffc(%ebp)
  400340:	8b 45 14             	mov    0x14(%ebp),%eax
  400343:	ff d0                	call   *%eax
  400345:	83 c4 10             	add    $0x10,%esp
  400348:	8d 45 f8             	lea    0xfffffff8(%ebp),%eax
  40034b:	ff 00                	incl   (%eax)
  40034d:	eb dd                	jmp    40032c <_fn_3+0x2c>
  40034f:	8d 45 fc             	lea    0xfffffffc(%ebp),%eax
  400352:	ff 00                	incl   (%eax)
  400354:	eb c4                	jmp    40031a <_fn_3+0x1a>
  400356:	c9                   	leave  
  400357:	c3                   	ret    
Disassembly of section .data:
