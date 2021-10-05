<?php
setcookie("cgi", "value", time() + (86400 * 30), "/");
?>

<!DOCTYPE html>
<html>
<head>
<!-- <link rel="stylesheet" href="index.css"> -->
<style>

body {
    background-image: linear-gradient(to right, rgb(65, 173, 141) , rgb(40, 80, 153));
}
h1 {
    color: mintcream;
    font-family: "Great Vibes", cursive;
    font-size: 165px;
    line-height: 160px;
    font-weight: normal;
    margin-bottom: 0px;
    margin-top: 40px;
    text-align: center;
    text-shadow: 0 1px 1px #fff;
    border-bottom: 3px solid rgb(0, 0, 0);
    /* display: inline; */
    /* border: 2px solid black;
    padding: 1px; */
}
input {
    width: 100%;
    height: 60px;
    border: 2px solid rgba(18, 70, 16, 0.342);
    border-radius: 4px;
    background-color: white;
    opacity: 100%;
}
.wra {
    position:absolute;
    top:50%;
    left:50%;
    width:300px; 
    height:200px; 
    margin-left:-150px;
    margin-top:-100px;
  }
</style>
</head>
<h1>
    WebSerV
</h1>
<body>

    <div class=wra>
        <form>  
            <!-- <label>Enter User name</label><br>   -->
            <!-- <input type="text" name="name" placeholder="Enter User name" size="30"><br>   -->
            <!-- <label>Enter Password</label><br>   -->
            <!-- <input type="text" name="email" placeholder="Enter Email" size="30"><br>   -->
            <!-- <br><input type="submit" value="Home"> -->
            <!-- <a href="home.php" br><input type="submit" value="Home"> >Go Home</a> -->
            <input type="button"  class="button_active" onclick="location.href='home1.php';" value="Home"/>
        </form>
    </div>
</body>
</html>