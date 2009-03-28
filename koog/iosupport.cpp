#include "iosupport.h"
#include "iomessage.h"

static const char * xpm_circle_black[] = {
"16 16 97 2",
"  	c None",
". 	c #5E4E4E",
"+ 	c #594949",
"@ 	c #554747",
"# 	c #534444",
"$ 	c #524343",
"% 	c #4F4242",
"& 	c #5B4B4B",
"* 	c #5F4D4D",
"= 	c #5A4A4A",
"- 	c #564747",
"; 	c #514444",
"> 	c #4E4040",
", 	c #493B3B",
"' 	c #413636",
") 	c #5E4D4D",
"! 	c #5F4E4E",
"~ 	c #594848",
"{ 	c #483B3B",
"] 	c #423636",
"^ 	c #403535",
"/ 	c #3F3434",
"( 	c #3D3131",
"_ 	c #332A2A",
": 	c #574747",
"< 	c #5D4C4C",
"[ 	c #554646",
"} 	c #473A3A",
"| 	c #3D3232",
"1 	c #3C3131",
"2 	c #3B3030",
"3 	c #3A3030",
"4 	c #372D2D",
"5 	c #2F2626",
"6 	c #251E1E",
"7 	c #574848",
"8 	c #554545",
"9 	c #453939",
"0 	c #392E2E",
"a 	c #382E2E",
"b 	c #382D2D",
"c 	c #342A2A",
"d 	c #2E2525",
"e 	c #261F1F",
"f 	c #211B1B",
"g 	c #504242",
"h 	c #544545",
"i 	c #4B3E3E",
"j 	c #362C2C",
"k 	c #352C2C",
"l 	c #322929",
"m 	c #2D2525",
"n 	c #191515",
"o 	c #4C3F3F",
"p 	c #4F4141",
"q 	c #443838",
"r 	c #352B2B",
"s 	c #2C2424",
"t 	c #241D1D",
"u 	c #161212",
"v 	c #4A3D3D",
"w 	c #3E3333",
"x 	c #392F2F",
"y 	c #312828",
"z 	c #2B2323",
"A 	c #141010",
"B 	c #463939",
"C 	c #3B3131",
"D 	c #2F2727",
"E 	c #282020",
"F 	c #1C1717",
"G 	c #120F0F",
"H 	c #3E3232",
"I 	c #342B2B",
"J 	c #221C1C",
"K 	c #151111",
"L 	c #0F0C0C",
"M 	c #332929",
"N 	c #302727",
"O 	c #241E1E",
"P 	c #181414",
"Q 	c #0C0A0A",
"R 	c #272020",
"S 	c #282121",
"T 	c #1F1919",
"U 	c #0A0808",
"V 	c #1A1515",
"W 	c #1E1818",
"X 	c #1D1818",
"Y 	c #1C1616",
"Z 	c #181313",
"` 	c #110D0D",
" .	c #090707",
"..	c #0F0D0D",
"+.	c #0D0A0A",
"@.	c #0C0909",
"#.	c #080707",
"                                ",
"          . + @ # $ %           ",
"        & * = - ; > , '         ",
"      ) ! ~ % { ] ^ / ( _       ",
"    : < [ } | 1 2 2 3 4 5 6     ",
"  7 + 8 9 3 0 a b b 4 c d e f   ",
"  g h i 1 a 4 j j j k l m 6 n   ",
"  o p q 3 b j j j j r l s t u   ",
"  { v w x 4 j j j j r y z f A   ",
"  B 9 C 0 4 j j j j c D E F G   ",
"  ] H a 4 r r r I c l s J K L   ",
"    I M y N N N D d z O P Q     ",
"      R e R S S R 6 T u U       ",
"        V F W X Y Z `  .        ",
"          K ..+.@.U #.          ",
"                                "};

static const char * xpm_circle_red[] = {
"16 16 96 2",
"  	c None",
". 	c #FF0000",
"+ 	c #ED0000",
"@ 	c #D70000",
"# 	c #DA0000",
"$ 	c #D00000",
"% 	c #CF0000",
"& 	c #C70000",
"* 	c #A80000",
"= 	c #EB0000",
"- 	c #C90000",
"; 	c #C50000",
"> 	c #C30000",
", 	c #C00000",
"' 	c #B30000",
") 	c #990000",
"! 	c #780000",
"~ 	c #E60000",
"{ 	c #BB0000",
"] 	c #B80000",
"^ 	c #B70000",
"/ 	c #B40000",
"( 	c #AA0000",
"_ 	c #970000",
": 	c #7B0000",
"< 	c #6B0000",
"[ 	c #FB0000",
"} 	c #C40000",
"| 	c #B90000",
"1 	c #B00000",
"2 	c #A60000",
"3 	c #950000",
"4 	c #7A0000",
"5 	c #530000",
"6 	c #FC0000",
"7 	c #E00000",
"8 	c #AF0000",
"9 	c #A50000",
"0 	c #920000",
"a 	c #760000",
"b 	c #4A0000",
"c 	c #EF0000",
"d 	c #F50000",
"e 	c #CD0000",
"f 	c #BD0000",
"g 	c #B60000",
"h 	c #B20000",
"i 	c #AE0000",
"j 	c #A20000",
"k 	c #8E0000",
"l 	c #6E0000",
"m 	c #430000",
"n 	c #E40000",
"o 	c #E20000",
"p 	c #C10000",
"q 	c #B50000",
"r 	c #B10000",
"s 	c #AB0000",
"t 	c #9C0000",
"u 	c #830000",
"v 	c #5E0000",
"w 	c #3B0000",
"x 	c #D90000",
"y 	c #AD0000",
"z 	c #AC0000",
"A 	c #A40000",
"B 	c #910000",
"C 	c #710000",
"D 	c #450000",
"E 	c #310000",
"F 	c #A10000",
"G 	c #9E0000",
"H 	c #8D0000",
"I 	c #500000",
"J 	c #280000",
"K 	c #800000",
"L 	c #7D0000",
"M 	c #820000",
"N 	c #850000",
"O 	c #790000",
"P 	c #670000",
"Q 	c #210000",
"R 	c #550000",
"S 	c #5D0000",
"T 	c #620000",
"U 	c #610000",
"V 	c #5B0000",
"W 	c #4E0000",
"X 	c #370000",
"Y 	c #1D0000",
"Z 	c #440000",
"` 	c #330000",
" .	c #2B0000",
"..	c #270000",
"+.	c #230000",
"@.	c #1C0000",
"                                ",
"          . . . . . .           ",
"        . . . . . . + @         ",
"      . . . . + # $ % & *       ",
"    . . . = - ; > > , ' ) !     ",
"  . . . ~ , { ] ^ ^ / ( _ : <   ",
"  . . [ } | / ' ' ' 1 2 3 4 5   ",
"  6 . 7 , ^ ' ' ' ' 8 9 0 a b   ",
"  c d e f g h ' ' h i j k l m   ",
"  n o p { q h h h r s t u v w   ",
"  x - | q 8 y y z ( A B C D E   ",
"    y * F G G G t _ H ! I J     ",
"      K L M N N M O P b Q       ",
"        R S T U V W X Y         ",
"          Z `  ...+.@.          ",
"                                "};

static const char * xpm_circle_yellow[] = {
"16 16 101 2",
"  	c None",
". 	c #FFFF00",
"+ 	c #FFF500",
"@ 	c #F7EB00",
"# 	c #F1E500",
"$ 	c #FFFB00",
"% 	c #F8EC00",
"& 	c #E7DB00",
"* 	c #CFC400",
"= 	c #B6AD00",
"- 	c #F9EC00",
"; 	c #D6CA00",
"> 	c #C1B700",
", 	c #BEB300",
"' 	c #B2A800",
") 	c #8A8300",
"! 	c #F6EB00",
"~ 	c #BCB200",
"{ 	c #B7AD00",
"] 	c #B5AB00",
"^ 	c #B2A900",
"/ 	c #A69D00",
"( 	c #888100",
"_ 	c #585300",
": 	c #F2E600",
"< 	c #AEA400",
"[ 	c #ABA200",
"} 	c #AAA100",
"| 	c #A79E00",
"1 	c #9E9500",
"2 	c #8C8500",
"3 	c #6D6700",
"4 	c #524D00",
"5 	c #FFF800",
"6 	c #FFFA00",
"7 	c #ACA200",
"8 	c #A39B00",
"9 	c #9A9200",
"0 	c #716B00",
"a 	c #3D3A00",
"b 	c #F8EB00",
"c 	c #F3E600",
"d 	c #EBDE00",
"e 	c #A39A00",
"f 	c #999100",
"g 	c #888000",
"h 	c #6E6800",
"i 	c #3F3C00",
"j 	c #E0D500",
"k 	c #E2D700",
"l 	c #C8BD00",
"m 	c #AFA600",
"n 	c #A9A000",
"o 	c #A59C00",
"p 	c #A29900",
"q 	c #968E00",
"r 	c #847D00",
"s 	c #666100",
"t 	c #D2C800",
"u 	c #CCC100",
"v 	c #B3AA00",
"w 	c #A89F00",
"x 	c #A49B00",
"y 	c #9F9600",
"z 	c #918900",
"A 	c #7A7300",
"B 	c #575300",
"C 	c #343100",
"D 	c #C7BD00",
"E 	c #B0A600",
"F 	c #A19800",
"G 	c #A09700",
"H 	c #989000",
"I 	c #877F00",
"J 	c #696300",
"K 	c #403D00",
"L 	c #282600",
"M 	c #928C00",
"N 	c #968D00",
"O 	c #938B00",
"P 	c #837C00",
"Q 	c #706A00",
"R 	c #4B4600",
"S 	c #252300",
"T 	c #696400",
"U 	c #6F6900",
"V 	c #797200",
"W 	c #7C7500",
"X 	c #605B00",
"Y 	c #454100",
"Z 	c #1F1D00",
"` 	c #3E3B00",
" .	c #5B5600",
"..	c #5A5500",
"+.	c #555000",
"@.	c #494500",
"#.	c #333100",
"$.	c #1B1A00",
"%.	c #242200",
"&.	c #1E1D00",
"*.	c #171600",
"                                ",
"          . . . + @ #           ",
"        . . . $ % & * =         ",
"      . . . . - ; > , ' )       ",
"    . . . ! ~ { ] ] ^ / ( _     ",
"  . . . : ^ < [ } } | 1 2 3 4   ",
"  . 5 6 { 7 | / / / 8 9 ) 0 a   ",
"  b c d ^ } / / / / e f g h i   ",
"  j k l m n o / / o p q r s a   ",
"  t u v < w o o o x y z A B C   ",
"  D E } w e F F G 1 H I J K L   ",
"    M q N O O O z 2 P Q R S     ",
"      T U V W W V Q X Y Z       ",
"        ` 4  ...+.@.#.$.        ",
"          C S S %.&.*.          ",
"                                "};

static const char * xpm_circle_green[] = {
"16 16 103 2",
"  	c None",
". 	c #15FF00",
"+ 	c #14FF00",
"@ 	c #13F300",
"# 	c #12E900",
"$ 	c #11E300",
"% 	c #16FF00",
"& 	c #17FF00",
"* 	c #14FA00",
"= 	c #12EC00",
"- 	c #12DD00",
"; 	c #0FCA00",
"> 	c #0DB400",
", 	c #13F500",
"' 	c #10D900",
") 	c #0FBF00",
"! 	c #0DB200",
"~ 	c #0DB100",
"{ 	c #0DA900",
"] 	c #0A8A00",
"^ 	c #11D700",
"/ 	c #0DAD00",
"( 	c #0DA700",
"_ 	c #0CA400",
": 	c #0C9900",
"< 	c #0A8100",
"[ 	c #075D00",
"} 	c #14FB00",
"| 	c #11D300",
"1 	c #0CA000",
"2 	c #0C9E00",
"3 	c #0C9D00",
"4 	c #0C9A00",
"5 	c #0B9200",
"6 	c #086800",
"7 	c #065400",
"8 	c #13F600",
"9 	c #12E800",
"0 	c #0B9900",
"a 	c #0B9700",
"b 	c #0B8E00",
"c 	c #098000",
"d 	c #044000",
"e 	c #12E400",
"f 	c #12E500",
"g 	c #0FCC00",
"h 	c #0B9600",
"i 	c #0B8D00",
"j 	c #097D00",
"k 	c #076500",
"l 	c #043D00",
"m 	c #10D300",
"n 	c #10D700",
"o 	c #0EB400",
"p 	c #0CA200",
"q 	c #0C9C00",
"r 	c #0B9800",
"s 	c #0B9500",
"t 	c #0A8B00",
"u 	c #097A00",
"v 	c #075E00",
"w 	c #043900",
"x 	c #0FC700",
"y 	c #0FC300",
"z 	c #0CA500",
"A 	c #0C9B00",
"B 	c #0A8600",
"C 	c #087000",
"D 	c #065100",
"E 	c #033100",
"F 	c #0EBC00",
"G 	c #0DAB00",
"H 	c #0C9F00",
"I 	c #0B9400",
"J 	c #0B9300",
"K 	c #0A8C00",
"L 	c #097C00",
"M 	c #076100",
"N 	c #043B00",
"O 	c #032800",
"P 	c #0B9100",
"Q 	c #0B8F00",
"R 	c #0A8700",
"S 	c #097900",
"T 	c #086700",
"U 	c #054500",
"V 	c #022200",
"W 	c #086900",
"X 	c #086F00",
"Y 	c #087200",
"Z 	c #065800",
"` 	c #021D00",
" .	c #044200",
"..	c #064E00",
"+.	c #065300",
"@.	c #054300",
"#.	c #032F00",
"$.	c #011900",
"%.	c #043500",
"&.	c #022700",
"*.	c #022400",
"=.	c #022100",
"-.	c #011600",
"                                ",
"          . . + @ # $           ",
"        % & + * = - ; >         ",
"      & % . , ' ) ! ~ { ]       ",
"    . % . ^ / { ( ( _ : < [     ",
"  } . + | _ 1 2 3 3 4 5 < 6 7   ",
"  @ 8 9 { 2 4 0 0 0 a b c 6 d   ",
"  e f g _ 3 0 0 0 0 h i j k l   ",
"  m n o p q r 0 0 r s t u v w   ",
"  x y z 1 A r r r r 5 B C D E   ",
"  F G H A h I I J 5 K L M N O   ",
"    P Q ] R R R B < S T U V     ",
"      W W X Y Y X 6 Z d `       ",
"         ...7 +...@.#.$.        ",
"          %.&.*.=.` -.          ",
"                                "};

static const char * xpm_sock_connecting[] = {
"16 16 11 1",
". c None",
"c c #000000",
"h c #585858",
"b c #808000",
"g c #808080",
"i c #a0a0a0",
"a c #c0c000",
"e c #c3c3c3",
"f c #dcdcdc",
"# c #ffff00",
"d c #ffffff",
"............####",
".........###aaab",
".........aaaabb.",
".........baaa...",
"...cc.....baaa..",
"..cdec....#aaaa.",
".cdffec..#aaabb.",
"cgefffec#aabb...",
"chgefffecbb.....",
"chhgefffec......",
".chegeffeic.....",
"..cdigefigc.....",
".cdighgighc.....",
"cdicchgghc......",
"dic..chhc.......",
"ic....cc........"};

static const char * xpm_sock_connected[] = {
"16 16 9 1",
". c None",
"# c #000000",
"d c #303030",
"g c #585858",
"f c #808080",
"b c #a0a0a0",
"e c #c3c3c3",
"c c #dcdcdc",
"a c #ffffff",
".............#ab",
"......###...#ab#",
".....#aaa#.#ab#.",
"....#accca#ab#..",
"...###bcccad#...",
"..#ae##bcccad...",
".#acce#dbccca#..",
"#feccce##bcce#..",
"#gfeccce#dbef#..",
"#ggfeccce##fg#..",
".#gefecceb#g#...",
"..#abfecbf##....",
".#abfgfbfg#.....",
"#ab##gffg#......",
"ab#..#gg#.......",
"b#....##........"};

static const char * xpm_sock_closed[] = {
"16 16 11 1",
". c None",
"b c #000000",
"c c #404000",
"h c #585858",
"g c #808080",
"i c #a0a0a0",
"a c #c0c000",
"e c #c3c3c3",
"f c #dcdcdc",
"# c #ffff00",
"d c #ffffff",
"................",
"................",
"................",
"........#a......",
"...bb..#ac......",
"..bdeb#ac.......",
".bdffebc...#a...",
"bgefffeb..#ac...",
"bhgefffeb#ac....",
"bhhgefffebc.....",
".bhegeffeib.....",
"..bdigefigb.....",
".bdighgighb.....",
"bdibbhgghb......",
"dib..bhhb.......",
"ib....bb........"};

static const char* xpm_sock_error[] = {
"15 15 103 2",
"Qt c None",
".L c None",
".# c None",
".h c None",
".X c #1a1414",
".4 c #1e1414",
".K c #291414",
"#H c #2f1414",
".z c #341414",
".p c #3b1414",
"#z c #411414",
".g c #541a16",
".f c #5c1d18",
".e c #5c1f1a",
".d c #612621",
"## c #642722",
".W c #671414",
".b c #672f2a",
"#y c #6a1414",
".a c #6a3936",
"#K c #6b1414",
".c c #703b36",
"#G c #761414",
".3 c #7a1414",
"#. c #7d1414",
".J c #8e1414",
".y c #901414",
"#J c #911414",
"#x c #961414",
".o c #a15c54",
".2 c #a61414",
".I c #a71414",
"#r c #ae7269",
"#F c #b41414",
".9 c #b51414",
"#I c #b51616",
"#E c #b71414",
"#l c #b81515",
"#D c #ba1414",
".x c #bb4744",
"#q c #bc1414",
"#C c #be2727",
".1 c #c0231c",
"#A c #c0231f",
".V c #c12c24",
"#w c #c13228",
"#s c #c15350",
"#B c #c2271f",
".8 c #c23333",
"#v c #c55047",
"#g c #c55252",
"#n c #c56058",
".w c #c56460",
"#f c #c65451",
"#p c #c75950",
"#u c #c85148",
".U c #ca544e",
"#t c #ca5953",
"#i c #ca655d",
".v c #ca7169",
"#e c #cb635c",
".7 c #cb655e",
"#b c #cb6661",
"#k c #ce6f67",
".H c #d16e66",
".u c #d27e78",
".R c #d46b66",
".T c #d46c67",
"#o c #d47d77",
".G c #d4817c",
".Z c #d77570",
".n c #d7a29c",
".A c #d97570",
".t c #d98680",
"#m c #d9a8a2",
".N c #da7d7a",
".6 c #da7f7b",
".s c #da807c",
".P c #db746f",
".r c #db7975",
".S c #dc7875",
"#j c #dc7a78",
"#c c #dc7b77",
".E c #dc7d78",
".C c #dd7772",
"#d c #dd7978",
".0 c #de7a78",
".F c #de7e7a",
".O c #df7e7d",
".B c #df7f7b",
".D c #df8580",
".m c #e6b9b5",
"#h c #e7b8b4",
".l c #eabeb9",
"#a c #eabfbb",
".5 c #f1c8c6",
".k c #f3d7d5",
".Y c #f3d8d7",
".j c #f3dada",
".i c #f6e7e7",
".M c #f6eceb",
".Q c #fef3f3",
".q c #ffffff",
"Qt.#Qt.#.a.b.c.d.e.f.gQtQtQtQt",
"QtQt.h.a.i.j.k.l.m.n.o.pQtQtQt",
"Qt.h.a.q.r.s.t.u.v.w.x.y.zQtQt",
"Qt.a.q.A.B.C.D.E.F.G.H.I.J.K.L",
".a.M.N.O.P.Q.R.S.T.Q.U.V.I.W.X",
".a.Y.Z.0.Q.Q.Q.T.Q.Q.Q.1.2.3.4",
".a.5.T.6.T.Q.Q.Q.Q.Q.7.8.9#..4",
"###a#b#c#d.T.Q.Q.Q#e#f#g.9#..4",
".e#h#i#j.T.Q.Q.Q.Q.Q#k#l.2#..4",
".f#m#n#o.Q.Q.Q#p.Q.Q.Q#q.2.3.4",
".g#r#s#t#u.Q#p#v#w.Q.9.2#x#y.X",
"Qt#z.y.I#A#B#C#D#E#F.2#x#G#H.L",
"QtQt.z.J.I.9#I.9.2.2#J#G#H.L.L",
".L.L.L.z#K.3#.#.#..3#y#HQtQtQt",
"QtQtQtQt.X.4.4.4.4.4.XQtQtQtQt"};

/* XPM */
static const char * xpm_size_0[] = {
"16 16 2 1",
" 	c None",
".	c #282222",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"                "};

/* XPM */
static const char * xpm_size_1[] = {
"16 16 3 1",
" 	c None",
".	c #513737",
"+	c #282222",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"  ++++++++++++  ",
"  ++++++++++++  ",
"                "};

/* XPM */
static const char * xpm_size_2[] = {
"16 16 4 1",
" 	c None",
".	c #7A3F3F",
"+	c #513737",
"@	c #282222",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"  ++++++++++++  ",
"  ++++++++++++  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"                "};

/* XPM */
static const char * xpm_size_3[] = {
"16 16 5 1",
" 	c None",
".	c #A33A3A",
"+	c #7A3F3F",
"@	c #513737",
"#	c #282222",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"  ++++++++++++  ",
"  ++++++++++++  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  ############  ",
"  ############  ",
"                "};

/* XPM */
static const char * xpm_size_4[] = {
"16 16 6 1",
" 	c None",
".	c #CC2828",
"+	c #A33A3A",
"@	c #7A3F3F",
"#	c #513737",
"$	c #282222",
"                ",
"                ",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"  ++++++++++++  ",
"  ++++++++++++  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  ############  ",
"  ############  ",
"  $$$$$$$$$$$$  ",
"  $$$$$$$$$$$$  ",
"                "};

/* XPM */
static const char * xpm_size_5[] = {
"16 16 7 1",
" 	c None",
".	c #F40909",
"+	c #CC2828",
"@	c #A33A3A",
"#	c #7A3F3F",
"$	c #513737",
"%	c #282222",
"                ",
"                ",
"                ",
"  ............  ",
"  ............  ",
"  ++++++++++++  ",
"  ++++++++++++  ",
"  @@@@@@@@@@@@  ",
"  @@@@@@@@@@@@  ",
"  ############  ",
"  ############  ",
"  $$$$$$$$$$$$  ",
"  $$$$$$$$$$$$  ",
"  %%%%%%%%%%%%  ",
"  %%%%%%%%%%%%  ",
"                "};

IOSupport::IOSupport( QObject *parent, const char *name )
          :QObject( parent, name )
{
        pm_16x16_Circle_Black    = QPixmap( xpm_circle_black );
        pm_16x16_Circle_Red      = QPixmap( xpm_circle_red );
        pm_16x16_Circle_Yellow   = QPixmap( xpm_circle_yellow );
        pm_16x16_Circle_Green    = QPixmap( xpm_circle_green );

        pm_16x16_Sock_Connecting = QPixmap( xpm_sock_connecting );
        pm_16x16_Sock_Connected  = QPixmap( xpm_sock_connected );
        pm_16x16_Sock_Closed     = QPixmap( xpm_sock_closed );
        pm_16x16_Sock_Error      = QPixmap( xpm_sock_error );

        pm_16x16_Size_0          = QPixmap( xpm_size_0 );
        pm_16x16_Size_1          = QPixmap( xpm_size_1 );
        pm_16x16_Size_2          = QPixmap( xpm_size_2 );
        pm_16x16_Size_3          = QPixmap( xpm_size_3 );
        pm_16x16_Size_4          = QPixmap( xpm_size_4 );
        pm_16x16_Size_5          = QPixmap( xpm_size_5 );
}

IOSupport::~IOSupport()
{
}


QStringList IOSupport::quoteSplit( const QString & text )
{
	QStringList list;
	QString data = text.stripWhiteSpace(  );
	QString tmp;

	int end = 0;

	while ( data.length(  ) )
	{
		if ( data.left( 1 ) == "\"" )
		{
			end = data.find( "\"", 1 );

			if ( end == -1 )
			{
				// parse error
				qWarning( "dequote parse error" );
				return list;
			}
		}
		else
		{
			end = data.find( " " );

			if ( end == -1 )
				end = data.length(  );
		}

		tmp = data.mid( 0, end );
		tmp = tmp.replace( QRegExp( "\"" ), "" );

		// no whitespace stripping here, b/c there is allowed
		// to be whitespace inside the quotes.

		list.append( tmp );
		data = data.mid( end + 1 );
		data = data.stripWhiteSpace(  );
	}

	return list;
}

QString IOSupport::quoteJoin( const QStringList & tmp )
{
        QStringList::Iterator it;
        QStringList list = tmp;
	QString result = "";

        for ( it = list.begin(); it != list.end(); ++it )
        {
		if ( (*it).contains( " " ) )
			result += "\"" + *it + "\" ";
		else
			result += *it + " ";
        }

	return result.stripWhiteSpace(  );
}

QString IOSupport::speedText( const QString & data )
{
        switch ( data.toInt() )
        {
        default:
                return "Unknown";
        case 0:
                return "Unknown";
        case 1:
                return "14.4";
        case 2:
                return "28.8";
        case 3:
                return "33.6";
        case 4:
                return "56.7";
        case 5:
                return "64k";
        case 6:
                return "128k";
        case 7:
                return "Cable";
        case 8:
                return "DSL";
        case 9:
                return "T1";
        case 10:
                return "T3+";
        }

        // should never get here
	return "** invalid **";
}

QString IOSupport::reverseSpeedText( const QString & data )
{
	if ( data == "Unknown" )
		return "0";
	else if ( data == "14.4" )
		return "1";
	else if ( data == "28.8" )
		return "2";
	else if ( data == "33.6" )
		return "3";
	else if ( data == "56.7" )
		return "4";
	else if ( data == "64k" )
		return "5";
	else if ( data == "128k" )
		return "6";
	else if ( data == "Cable" )
		return "7";
	else if ( data == "DSL" )
		return "8";
	else if ( data == "T1" )
		return "9";
	else if ( data == "T3+" )
		return "10";

        // should never get here
	return "0";
}

QString IOSupport::sizeText( const QString & data )
{
	float bb = data.toFloat(  );
	float ref_kb = ( 1024 );
	float ref_mb = ( 1024 * 1024 );
	float ref_gb = ( 1024 * 1024 * 1024 );

	QString text;

	if ( bb < ref_mb )
		text.sprintf( "%2.2f Kb", bb / ref_kb );
	else if ( bb < ref_gb )
		text.sprintf( "%2.2f Mb", bb / ref_mb );
	else
		text.sprintf( "%2.2f Gb", bb / ref_gb );
	return text;
}

QString IOSupport::timeText( const QString & data )
{
	Q_INT32 orig = data.toInt(  );
	Q_INT32 secs = orig % 60;
	Q_INT32 mins = orig / 60;

	QString text;
	text.sprintf( "%2d:%2.2d", mins, secs );
	return text;
}

QString IOSupport::stripDir( const QString & data )
{
	return QString( data ).replace( QRegExp( "^.*\\" ), "" );
}

QString IOSupport::stripFile( const QString & data )
{
	return QString( data ).replace( QRegExp( "\\.*$" ), "" );
}

QString IOSupport::networkToAscii( const QString & data )
{
	Q_UINT32 ip32 = data.toUInt(  );
	QString text;

	text.sprintf( "%d.%d.%d.%d",
		        ( ip32 >> 0  ) & 0xff,
		        ( ip32 >> 8  ) & 0xff,
		        ( ip32 >> 16 ) & 0xff,
                        ( ip32 >> 24 ) & 0xff );

	return text;
}

QString IOSupport::floatToString( float num, const char * fmt )
{
        return QString().sprintf( fmt, num );
}

const QPixmap & IOSupport::bitratePixmap( const QString & data )
{
        Q_INT32 num = data.toInt();

        if ( num <= 112 )
                return pm_16x16_Size_0;
        if ( num <= 128 )
                return pm_16x16_Size_1;
        if ( num <= 160 )
                return pm_16x16_Size_2;
        if ( num <= 192 )
                return pm_16x16_Size_3;
        if ( num <= 224 )
                return pm_16x16_Size_4;
        return pm_16x16_Size_5;
}

const QPixmap & IOSupport::ratePixmap( const QString & data )
{
        Q_INT32 num = data.toInt();

        if ( num < 2 )
                return pm_16x16_Circle_Black;
        if ( num < 10 )
                return pm_16x16_Circle_Red;
        if ( num < 20 )
                return pm_16x16_Circle_Yellow;
        return pm_16x16_Circle_Green;
}

const QPixmap & IOSupport::speedPixmap( const QString & data )
{
        Q_INT32 num = data.toInt();

        if ( num <= 3 )
                return pm_16x16_Circle_Black;
        if ( num <= 6 )
                return pm_16x16_Circle_Red;
        if ( num <= 8 )
                return pm_16x16_Circle_Yellow;
        return pm_16x16_Circle_Green;
}

const QPixmap & IOSupport::sizePixmap( const QString & data )
{
        Q_INT32 num = data.toInt();

        if ( num < 100000 )
                return pm_16x16_Size_0;
        if ( num < 1000000 )
                return pm_16x16_Size_1;
        if ( num < 3000000 )
                return pm_16x16_Size_2;
        if ( num < 6000000 )
                return pm_16x16_Size_3;
        if ( num < 10000000 )
                return pm_16x16_Size_4;
        return pm_16x16_Size_5;
}

QString IOSupport::replaceCarets( const QString & data )
{
        QString fixed = data;
        fixed.replace( QRegExp( "<" ), "&lt;" );
        fixed.replace( QRegExp( ">" ), "&gt;" );
        return fixed;
}

