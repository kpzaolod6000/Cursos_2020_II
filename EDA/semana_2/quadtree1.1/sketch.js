let qt;
let count = 0;

function setup(){
    createCanvas(400,400);
    let boundary = new Rectangle(200,200,200,200);
    qt = new QuadTree(boundary,4);
    console.log(qt);
    for (let i = 0; i < 2000; i++){  
        let p = new Point(Math.random()*400,Math.random()*400);
        qt.insert(p);
    }
    
    background(0);
    qt.show();
    //console.log(random(10))
    /*stroke (0 ,255 ,0) ;
    rectMode (CENTER);
    let range = new Rectangle(random(200),random(200),random(50),random(50))
    rect (range.x, range.y, range.w*2 , range.h *2) ;
    let points = [];
    qt.query(range , points );
    let numpoints = 0;
    for (let p of points ){
        strokeWeight(4) ;
        point(p.x, p.y);
        numpoints++;
    }
    console.log(count);
    console.log(numpoints);*/

}
function draw () {
    background (0);
    qt. show () ;
    if(mouseIsPressed){
        stroke (0 ,255 ,0);
        rectMode (CENTER);
        let range = new Rectangle(mouseX,mouseY,50,50);
        rect (range.x, range.y, range.w*2 , range.h *2) ;
        let points = [];
        qt.query(range , points );
        let numpoints = 0;
        for (let p of points ){
            strokeWeight(4) ;
            point(p.x, p.y);
            numpoints++;
        }
        console.log(count);
        console.log(numpoints);
    }
}
    
/*
function draw(){//sin el recaudro
    background(0);
    if(mouseIsPressed){
        for (let i = 0; i < 1; i++){  
            let m = new Point(mouseX+random(-5,5),mouseY+random(-5,5));
            qt.insert(m);
        }
    }
    background(0);
    qt.show();
}*/