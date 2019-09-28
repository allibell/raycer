var BoudingBoxOr = new Class({
  createCanvas: function() {
    var canvas = new Canvas(320, 240);
    
    canvas.add(new Rectangle(new Vector(2, -4), new Vector(5, 2), "dashed"));
    canvas.add(new Rectangle(new Vector(4, -6), new Vector(4, 3), "dashed"));
    canvas.add(new Rectangle(new Vector(2, -6), new Vector(6, 4)));
    
    return canvas.toSVG();
  }
});

(function(scriptElement) {
  var figure = new BoudingBoxOr();
  
  scriptElement.parentNode.appendChild(figure.createCanvas());
})(document.scripts[document.scripts.length - 1]);
