//Player options
window.addEventListener("load", function() {
    //Play/pause button events
    document.getElementById("player_btn").addEventListener("click", function(){
        if (this.src.endsWith("pause.png")) {
            this.src = "res/img/play.png";
            document.getElementById("player_src").pause();
        } else {
            this.src = "res/img/pause.png";
            document.getElementById("player_src").play();
        }
    });

    //Show pause button if track played
    document.getElementById("player_src").addEventListener("play", function(){
        document.getElementById("player_btn").src = "res/img/pause.png";
    });
    //Close player
    document.getElementById("player_close_btn").addEventListener("click", function(){
        document.getElementById("player_src").pause();
        showPlayer(false);
    });
});

function showPlayer(b) {
    document.getElementById("player").style.display = b ? "block" : "none";
    document.getElementById("content").style.bottom = b ? "55px" : "0";
}

function playFile(fileName) {
    document.getElementById("player_text").innerText = fileName;
    document.getElementById("player_text").textContent = fileName;

    document.getElementById("player_src").src = "view?path=" + encodeURIComponent(state.currentPath + "/" + fileName);
    document.getElementById("player_src").play();
}
function updateTimeline(currenttime, duration) {
    document.getElementById("player_timeline").value = currenttime/duration*100;
}

function setPlayerTime(val) {
    document.getElementById("player_src").currentTime = document.getElementById("player_src").duration/100*val;
}
