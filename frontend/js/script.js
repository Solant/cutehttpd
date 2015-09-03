var state = {}

function cd(path) {
    var xhr = new XMLHttpRequest();
    xhr.open("GET", "cd?path=" + encodeURIComponent(path), true);
    if (xhr.overrideMimeType) {
        xhr.overrideMimeType("application/json");
    }
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            state = JSON.parse(xhr.responseText);
            update();
        }
    }
    xhr.send();
}

function download(path, filename) {
    var dl = document.createElement("a");
    dl.setAttribute("display", "none");
    dl.setAttribute("href", "download?path=" + encodeURIComponent(path));
    dl.setAttribute("download", filename);
    document.getElementById("content").appendChild(dl);
    dl.click();
}

function setCurrentPath(path) {
    document.getElementById("path").innerHTML = "";
    var folders = path.split("/");
    var newDiv = document.createElement("div");
    newDiv.className = "path-element";
    newDiv.innerText = "Root";
    newDiv.textContent = "Root";
    document.getElementById("path").appendChild(newDiv);
    newDiv.addEventListener("click", function(){
    cd("/");
    });
    var separator = document.createElement("span");
    separator.innerText = "/";
    separator.textContent = "/";
    document.getElementById("path").appendChild(separator);
    var closuredPath = "/";
    for (var i = 0; i < folders.length; i++) {
    if (folders[i] != "") {
        var newPathElementDiv = document.createElement("div");
        newPathElementDiv.innerText = folders[i];
        newPathElementDiv.textContent = folders[i];
        newPathElementDiv.className = "path-element";
        document.getElementById("path").appendChild(newPathElementDiv);
        closuredPath += folders[i] += '/';
        newPathElementDiv.addEventListener("click", function(path) {
        return function() {
            cd(path);
        }
        }(closuredPath));

        var separator2 = document.createElement("span");
        separator2.innerText = "/";
        separator2.textContent = "/";
        document.getElementById("path").appendChild(separator2);
    }
    }
}

function createElement(icon, fileName, type) {
    var newElement = document.createElement("div");
    newElement.className = "element";
    if (type == "folder") {
    newElement.addEventListener("click", function() {
        cd(state.currentPath + "/" + fileName);
    });
    }
    if (type == "file") {
    newElement.addEventListener("click", function () {
        //Create menu if file was clicked
        showLense(true);
        showMenu(true ,fileName);
    });
    }
    var newImage = document.createElement("img");
    newImage.src = icon;
    var newName = document.createElement("span");
    newName.className = "name";
    newName.innerText = fileName;
    newName.textContent = fileName;
    newElement.appendChild(newImage);
    newElement.appendChild(newName);
    document.getElementById("content").appendChild(newElement);
}

function showContent() {
    document.getElementById("content").innerHTML = "";
    for (var i = 0; i < state.folders.length; i++) {
    createElement("res/img/folder.png", state.folders[i], "folder");
    }
    for (var i = 0; i < state.files.length; i++) {
    createElement("res/img/file.png", state.files[i], "file");
    }
}

function update() {
    setCurrentPath(state.currentPath);
    showContent();
}

function showLense(b) {
    document.getElementById("lense").style.display = b ? "block" : "none";
}

function showMenu(b, fileName) {
    document.getElementById("menu").style.display = b ? "block" : "none";
    if (fileName === undefined) {
        return;
    }

    //Get file extension
    var fileExtension = fileName.split(".");
    fileExtension = fileExtension[fileExtension.length-1];

    //Create menu
    var menu = document.getElementById("menu");
    menu.innerHTML = "";

    //Add Download button
    var newDiv = document.createElement("div");
    newDiv.className = "menu-element";
    newDiv.innerText = "Download";
    newDiv.textContent = "Download";
    newDiv.addEventListener("click", function(fileName){
        return function() {
            download(state.currentPath + "/" + fileName, fileName);
        }
    }(fileName));
    menu.appendChild(newDiv);

    //Show as text
    newDiv = document.createElement("div");
    newDiv.className = "menu-element";
    newDiv.innerText = "Show as text";
    newDiv.textContent = "Show as text";
    newDiv.addEventListener("click", function(fileName){
        return function() {
            showText(true, fileName);
        }
    }(fileName));
    menu.appendChild(newDiv);

    //Check if music
    if (fileExtension == "mp3" || fileExtension == "ogg" || fileExtension == "wav") {
        newDiv = document.createElement("div");
        newDiv.className = "menu-element";
        newDiv.innerText = "Play";
        newDiv.textContent = "Play";
        newDiv.addEventListener("click", function(fileName){
            return function() {
                showLense(false);
                showMenu(false);
                showPlayer(true);
                playFile(fileName);
            }
        }(fileName));
        menu.appendChild(newDiv);
    }

    //Check if image
    if (fileExtension == "jpeg" || fileExtension == "jpg" || fileExtension == "png" || fileExtension == "gif") {
        newDiv = document.createElement("div");
        newDiv.className = "menu-element";
        newDiv.innerText = "Show";
        newDiv.textContent = "Show";
        newDiv.addEventListener("click", function(fileName){
            return function() {
                showLense(true);
                showMenu(false);
                showImage(true, fileName);
            }
        }(fileName));
        menu.appendChild(newDiv);
    }

    //Close
    newDiv = document.createElement("div");
    newDiv.className = "menu-element";
    newDiv.innerText = "Nothing";
    newDiv.textContent = "Nothing";
    newDiv.addEventListener("click", function(){
        document.getElementById("menu").style.display = "none";
        document.getElementById("lense").style.display = "none";
    });
    menu.appendChild(newDiv);
}

window.addEventListener("load", function(){
    cd("/");
});

//Hide menu and lense on lense click
window.addEventListener("load", function(){
    document.getElementById("lense").addEventListener("click", function(){
        showLense(false);
        showMenu(false);
    });
});

function showText(b, fileName) {
    document.getElementById("text_viewer").style.display = b ? "block" : "none";
    if (fileName === undefined) {
        return;
    }

    var xhr = new XMLHttpRequest();
    xhr.open("POST", "download?path="+encodeURIComponent(state.currentPath + "/" + fileName), true);
    xhr.overrideMimeType("application/json");
    xhr.onreadystatechange = function() {
        if (xhr.readyState == 4 && xhr.status == 200) {
            document.getElementById("text_viewer_src").textContent = xhr.responseText;
            document.getElementById("text_viewer_src").className = "";
            hljs.highlightBlock(document.getElementById("text_viewer_src"));
        }
    }
    xhr.send();
}

//Hide text format section
window.addEventListener("load", function(){
    document.getElementById("lense").addEventListener("click", function(){
        showLense(false);
        showText(false);
    });
});
