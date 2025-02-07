//let 关键字是 ES6 新增的，用于声明块作用域的变量。与 var 不同，
//let 声明的变量仅在声明它的块级作用域内有效，并且不能被重复声明。

let x = 10; // 块级作用域变量
if(true){
    let y = 20;
    console.log(x);// 输出 10
}
console.log(y); // 报错：y is not defined