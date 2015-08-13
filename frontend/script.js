var state = {}

function cd(path) {
    var xhr = new XMLHttpRequest();
    xhr.open("POST", "cd", true);
    xhr.overrideMimeType("application/json");
    var params = "path=" + encodeURIComponent(path);
    xhr.onreadystatechange = function() {
    if (xhr.readyState == 4 && xhr.status == 200) {
        //console.log(xhr.responseText);
        state = JSON.parse(xhr.responseText);
        update();
    }
    }
    xhr.send(params);
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
    createElement("folder.png", state.folders[i], "folder");
    }
    for (var i = 0; i < state.files.length; i++) {
    createElement("file.png", state.files[i], "file");
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

    //Check if music
    if (fileExtension == "mp3") {
        newDiv = document.createElement("div");
        newDiv.className = "menu-element";
        newDiv.innerText = "Play";
        newDiv.textContent = "Play";
        newDiv.addEventListener("click", function(fileName){
            return function() {
                alert("Playing");
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

window.onload = cd("/");
