// JavaScript 提供了许多常用的事件，用于在用户与网页交互时执行特定的代码。
// 以下是一些常用的 JavaScript 事件及其简要说明：

// 鼠标事件

// onclick：当用户点击某个元素时触发。
element.onclick = function() {
    console.log("Element clicked");
};


// ondblclick：当用户双击某个元素时触发。
element.ondblclick = function() {
    console.log("Element double-clicked");
};

// onmouseover：当鼠标指针移动到某个元素上时触发。
element.onmouseover = function() {
    console.log("Mouse over element");
};

// onmouseout：当鼠标指针移出某个元素时触发。
element.onmouseout = function() {
    console.log("Mouse out of element");
};

// onmousemove：当鼠标指针在元素上移动时触发。
element.onmousemove = function() {
    console.log("Mouse move over element");
};

// onmousedown：当用户按下鼠标按钮时触发。
element.onmousedown = function() {
    console.log("Mouse button down on element");
};

// onmouseup：当用户释放鼠标按钮时触发。
element.onmouseup = function() {
    console.log("Mouse button released on element");
};


// 键盘事件

// onkeydown：当用户按下键盘按键时触发。
element.onkeydown = function(event) {
    console.log("Key down: " + event.key);
};

// onkeypress：当用户按下并按住一个键时触发。
element.onkeypress = function(event) {
    console.log("Key press: " + event.key);
};

// onkeyup：当用户释放键盘按键时触发。
element.onkeyup = function(event) {
    console.log("Key up: " + event.key);
};


// 表单事件

// onfocus：当元素获得焦点时触发。
element.onfocus = function() {
    console.log("Element focused");
};

// onblur：当元素失去焦点时触发。
element.onblur = function() {
    console.log("Element lost focus");
};

// onchange：当元素的值改变时触发（通常用于 <input>、<textarea> 和 <select> 元素）。
element.onchange = function() {
    console.log("Element value changed");
};

// onsubmit：当表单提交时触发。
form.onsubmit = function() {
    console.log("Form submitted");
    return false; // 阻止表单提交
};

// onreset：当表单重置时触发。
form.onreset = function() {
    console.log("Form reset");
};


// 加载事件

// onload：当页面或图像加载完成时触发。
window.onload = function() {
    console.log("Page loaded");
};

// onunload：当用户离开页面时触发。
window.onunload = function() {
    console.log("Page unloaded");
};


// 其他事件

// onresize：当窗口或框架的大小改变时触发。
window.onresize = function() {
    console.log("Window resized");
};

// onscroll：当元素的滚动条被滚动时触发。
window.onscroll = function() {
    console.log("Window scrolled");
};

// oncontextmenu：当鼠标右键单击元素时触发。
element.oncontextmenu = function() {
    console.log("Context menu opened");
    return false; // 阻止默认的上下文菜单
};

// 事件监听器

// 除了直接在元素上设置事件处理程序，还可以使用 addEventListener 方法添加事件监听器：
element.addEventListener('click', function() {
    console.log('Element clicked');
});

// 这种方法的优势是可以为同一个事件添加多个处理程序，并且更具灵活性。

// 这些事件在实际开发中非常常用，了解它们的使用场景和如何处理它们将有助于你更好地与用户交互。