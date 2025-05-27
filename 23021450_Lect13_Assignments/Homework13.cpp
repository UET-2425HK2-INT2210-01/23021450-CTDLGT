// 1. /<[^>]+>/
//   1.1 <an xml tag>
//   1.2 <opentag> <closetag>
//   1.3 </closetag>
//   1.5 <with attribute=”77”>
// 2. /a.[bc]+/
//   2.1 abc
//   2.2 abbbbbbbb
//   2.3 azc
//   2.4 abcbcbcbc
//   2.6 azccbbbbcbccc
// 3. /(very )+(fat)?(tall|ugly) man/
//   3.1 very fat man
//   3.3 very very fat ugly man
//   3.4 very very very tall man
// 4. Chuỗi dạng "abc.def.ghi.jkx"
//   ^.{3}\..{3}\..{3}\..{3}$
// 5. Số điện thoại
//   ^(\(\d{3}\)|^\d{3})[-. ]?\d{3}[-. ]?\d{4}$
// 6. Chuỗi validate
//   ^(?!.*[-_ ]{2})[a-zA-Z0-9]+(?:[-_ ][a-zA-Z0-9]+)*$