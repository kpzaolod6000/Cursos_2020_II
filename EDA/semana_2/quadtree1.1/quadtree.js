class Point {
    constructor (x, y){
        this.x = x;
        this.y = y;
        //this.userData = userData;
    }
}

class Rectangle{
    constructor (x, y, w, h){
    this.x = x; // center
    this.y = y;
    this.w = w; // half width
    this.h = h; // half height
    }

    // verifica si este objeto contiene un objeto Punto 
    contains(point){
        if(point.x >= this.x - this.w && point.x <= this.x + this.w && point.y >= this.y - this.h && point.y <= this.y + this.h){
            return true;
        }
        return false;
    }
    //verifica 
    intersects(range){
        if(range.x - range.w > this.x + this.w || range.x + range.w < this.x - this.w || 
            range.y - range.h > this.y + this.h || range.y + range.h < this.y - this.h){
            return false;//si se cumple esto nose intersecta por lo tanto devuelve falso
        }
        return true;
    }
        
}

class QuadTree {
    constructor(boundary,n){
    this.boundary = boundary ; // Rectangle
    this.capacity = n; // capacidad maxima de cada cuadrante
    this.points = []; // vector , almacena los puntos a almacenar
    this.divided = false;
    }
    subdivide(){
        let x = this.boundary.x;
        let y = this.boundary.y;
        let w = this.boundary.w;
        let h = this.boundary.h;
        
        let se = new Rectangle(x+w/2,y+h/2,w/2,h/2);
        this.southeast = new QuadTree(se,this.capacity);
        
        let sw = new Rectangle(x-w/2,y+h/2,w/2,h/2);
        this.southwest = new QuadTree(sw,this.capacity);
        
        let ne = new Rectangle(x+w/2,y-h/2,w/2,h/2);
        this.northeast = new QuadTree(ne,this.capacity);

        let nw = new Rectangle(x-w/2,y-h/2,w/2,h/2);
        this.northwest = new QuadTree(nw,this.capacity);
        
        this.divided = true;

// this . northwest = qt_northwest ;
// this . southeast = qt_southeast ;
// this . southwest = qt_southwest ;

    }

    insert(point){
        if(!this.boundary.contains(point)){
            return;
        }
        if(this.points.length < this.capacity){
            this.points.push(point)
        }else{
            if(!this.divided){
                this.subdivide(); 
            }
            this.northeast.insert(point);
            this.northwest.insert(point);
            this.southeast.insert(point);
            this.southwest.insert(point);
        }
    }

    query(range , found ){
        if(!found){
            found = [];
        }
        if(!this.boundary.intersects(range)){//sino se intersectan
            return found;
        }//cuando se instersectan
        for(let i = 0; i < this.points.length; i++){
            if(range.contains(this.points[i])){
                found.push(this.points[i]);
            }
            count++;
        }
        if(!this.divided){
            return;
        }
        this.northeast.query(range,found);
        this.northwest.query(range,found);
        this.southeast.query(range,found);
        this.southwest.query(range,found);
        return found;
    }

    show(){
        stroke(225);
        strokeWeight(1);
        noFill();
        rectMode(CENTER);
        rect(this.boundary.x,this.boundary.y,this.boundary.w*2,this.boundary.h*2);
        if(this.divided){
            this.northeast.show();
            this.northwest.show();
            this.southeast.show();
            this.southwest.show();
        }
        for(let p of this.points){
            strokeWeight(4);
            point(p.x,p.y);
        }
    }
}