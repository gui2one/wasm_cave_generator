export default class Color {

    constructor(r, g, b) {
        this.r = r;
        this.g = g;
        this.b = b;
    }

    componentToHex(c) {
        var hex = c.toString(16);
        return hex.length == 1 ? "0" + hex : hex;
    }
    toHexString() {
        return "#" + this.componentToHex(this.r) + this.componentToHex(this.g) + this.componentToHex(this.b);
    }

    clamp(val, min, max) {
        if (val < min) return min;
        else if (val > max) return max;
        else return val;
    }
    set(r, g, b) {
        this.r = this.clamp(r, 0, 255);
        this.g = this.clamp(g, 0, 255);
        this.b = this.clamp(b, 0, 255);
    }
}