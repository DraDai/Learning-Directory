window.onload = function(){
    //获取所有的li
    var body_lis = document.getElementById("body-ul").getElementsByTagName("li");
    //设置当前焦点元素索引为0
    var current_index = 0;
    //打开定时器
    var timer = setInterval(setChange, 5000);

    //遍历元素
    for(let i = 0; i < body_lis.length; i++){
        //添加鼠标点击事件
        body_lis[i].onclick = function(){
            clearInterval(timer);
            if(i != current_index){
                
                switchLi(i);
            }
            timer = setInterval(setChange, 5000);
        }

    }

    function setChange(){
        ++current_index;
        //索引达到上限自动归零
        if(current_index == body_lis.length){
            current_index = 0;
        }

        switchLi(current_index);
    }

    function switchLi(index){
        var body_img = document.getElementById("body").getElementsByTagName("img");
        for(let i = 0; i < body_lis.length; i++){
            if(i != index){
                body_lis[i].classList.remove("li-current");
                body_img[i].classList.remove("img-current");
            }else{
                body_img[i].classList.add("img-current");
                body_lis[i].classList.add("li-current");
            }
        }
        current_index = index;
    }
}