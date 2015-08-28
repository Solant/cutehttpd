var imageList = [];

//Image formats for filter function
var imageFormats = [".png", ".gif", ".jpg", ".jpeg"];

//Init actions
window.addEventListener("load", function(){
    //Hide image
    document.getElementById("lense").addEventListener("click", function(){
        showImage(false);
    });
    //Next image
    document.getElementById("viewer_button_right").addEventListener("click", function() {
        showNextImage();
    });
    //Prev image
    document.getElementById("viewer_button_left").addEventListener("click", function() {
        showPrevImage();
    });
});

//Arrow keys to switch images
window.addEventListener("keydown", function(event){
    if (document.getElementById("viewer").style.display == "block") {
        if (event.keyCode == 37) {
            showPrevImage();
        }
        if (event.keyCode == 39) {
            showNextImage();
        }
    }
});

function showImage(b, fileName) {
    document.getElementById("viewer").style.display = b ? "block" : "none";
    if (fileName === undefined) {
        return;
    }
    loadImageList();
    document.getElementById("viewer_counter").textContent = (imageList.indexOf(fileName)+1) +  " of " + imageList.length;
    document.getElementById("viewer_src").src = "download?path=" + encodeURIComponent(state.currentPath + "/" + fileName);
}

function loadImageList() {
   imageList = state.files.filter(isImage);
}

function isImage(fileName) {
    for (var i = 0; i < imageFormats.length; i++) {
        if(fileName.endsWith(imageFormats[i])){
            return true;
        }
    }
    return false;
}

function showNextImage() {
    var currIndex = decodeURIComponent(document.getElementById("viewer_src").src).split("/");
    currIndex = imageList.indexOf(currIndex[currIndex.length-1]);
    var nextIndex = (currIndex+1)%imageList.length;         //get next index or 0 if nextIndex = imageList length
    document.getElementById("viewer_src").src = "download?path=" + encodeURIComponent(state.currentPath + "/" + imageList[nextIndex]);
    document.getElementById("viewer_counter").textContent = (nextIndex + 1) +  " of " + imageList.length;
}

function showPrevImage() {
    var currIndex = decodeURIComponent(document.getElementById("viewer_src").src).split("/");
    currIndex = imageList.indexOf(currIndex[currIndex.length-1]);
    var nextIndex = (currIndex-1+imageList.length)%imageList.length;        
    document.getElementById("viewer_src").src = "download?path=" + encodeURIComponent(state.currentPath + "/" + imageList[nextIndex]);
    document.getElementById("viewer_counter").textContent = (nextIndex + 1) +  " of " + imageList.length;
}
