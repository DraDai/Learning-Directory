/*在早期的 JavaScript 版本中，使用 var 关键字来声明变量是最常见的方式。
var 声明的变量可以是全局变量或局部变量，而且可以被重复声明。*/
var x = 10;     //全局变量
function example(){
    var y = 20;     //局部变量
    console.log(x);     //输出10
}