/*class Point {
    constructor (x, y){
        this.x = x;
        this.y = y;
        //this.userData = userData;
    }
}*/
class Point {
    constructor(x, y){
        this.x = x;
        this.y = y;
        //this.userData = userData;
    }
}

k = 2;
class Node {
    constructor(point,axis){
        this.point = point;
        this.left = null;
        this.right = null;
        this.axis = axis;
    }
}
function getHeight(node){
    if (!node)
        return;
    console.log(node.point);
    getHeight(node.left);
    getHeight(node.right);
}
function generate_dot (node){}
function build_kdtree(points,depth = 0){
    if(points.length == 0){
        console.log("hola");
        return null;
    }
    n   = points.length;
    m   = points[0].length;
    eje = depth % m;

    //console.log(n); 
    //console.log(m); 
    console.log(eje);
    

    points.sort((a,b)=>a[eje] - b[eje]);
    console.log(points);
    median = Math.floor(points.length/2);
    
    let izq = [];
    let der = [];
    for(let i = 0 ; i < median; i++)
        izq.push(points[i]);
    for(let i = median+1 ; i < n; i++)
        der.push(points[i]);

    
    let node = new Node(points[median],eje);
    console.log("nodo",node.point);
    console.log(izq);
    console.log(der);

    
    node.left = build_kdtree(izq,depth++); 
    node.right = build_kdtree(der,depth++); 


    /*
    let array = [];
    for(let i = 0; i < n ; i++){
        array.push(points[i][eje]);
    }
    array.sort(function(a, b){return a-b});
    console.log(array);
    //console.log(points[0]*100);
    median = Math.floor(array.length/2);
    
    let point;
    for(let i = 0; i < n ; i++){
        if(array[median] == points[i][eje]){
            point = points[i];
            break;
        }
    }
    console.log(point);
    
    let izq = [];
    let der = [];
    for(let i = 0 ; i < median; i++)
        izq[i] = array[i];
    for(let i = median+1 ; i < n; i++)
        der.push(array[i]);

    let node = new Node(point,eje);
    console.log("nodo",node.point);
    //node.left = build_kdtree(,depth++); 
    //node.right = build_kdtree(,depth++); 
    console.log(izq);
    console.log(der);
    */
    return node;

}
const arr = [[10, 4], [40, 32], [67, 12], [43, 31], [65, 1]];
arr.sort((a,b)=>a[0] - b[0]);
console.log(arr);
console.log(arr[0]);
console.log(arr[5]);
//let mu = []
//mu = arr.slice(1,4);
//console.log(mu);
let root = build_kdtree(arr);
getHeight(root);

