window.onload = function(){
     //获取所有的li
    var bodyLis = document.getElementById("carousel-ul").getElementsByTagName("li");
    //获取所有的img
    var bodyImgs = document.getElementById("carousel").getElementsByClassName("carousel-img");
    //获取所有的arrow
    var arrows = document.getElementsByClassName("carousel-arrow");
    //设置当前焦点元素索引为0
    var currentIndex = 0;
    //打开定时器
    var timer = setInterval(setChange, 5000);

    // 鼠标悬停时显示箭头
    document.getElementById("carousel").onmouseover = function() {
        for (let arrow of arrows) {
            arrow.style.display = "block";
        }
    }

    // 鼠标离开时隐藏箭头
    document.getElementById("carousel").onmouseleave = function() {
        for (let arrow of arrows) {
            arrow.style.display = "none";
        }
    }

    //点击左箭头向前切换图片
    document.getElementById("arrow-left").onclick = function(){
        //清除定时器
        clearInterval(timer);
        --currentIndex;
        //索引达到下限自动切换最后
        if(currentIndex == -1){
            currentIndex = bodyImgs.length - 1;
        }
        //切换图片
        switchimg(currentIndex);
        //添加定时器
        timer = setInterval(setChange, 5000);
    }

    //点击右箭头向后切换图片
    document.getElementById("arrow-right").onclick = function(){
        //清除定时器
        clearInterval(timer);
        ++currentIndex;
        //索引达到上限限自动归零
        if(currentIndex == bodyImgs.length){
            currentIndex = 0;
        }
        //切换图片
        switchimg(currentIndex);
        //添加定时器
        timer = setInterval(setChange, 5000);
    }

    //轮播函数
    function setChange(){
        ++currentIndex;
        //索引达到上限自动归零
        if(currentIndex == bodyImgs.length){
            currentIndex = 0;
        }

        switchimg(currentIndex);
    }

    //切换图片函数
    function switchimg(index){
        for(let i = 0; i < bodyImgs.length;i++){
            if(i != index){
                bodyLis[i].classList.remove("li-current");
                bodyImgs[i].classList.remove("img-current");
            }else{
                bodyImgs[i].classList.add("img-current");
                bodyLis[i].classList.add("li-current");
            }
        }
        currentIndex = index;
    }

}


