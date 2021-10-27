import Color from "../js/Color"
import createModule from "./cave_generator"
import { Pane } from "tweakpane"
let generator;
let color = new Color(0, 0, 255);

const PARAMS = {
    threshold: 100,
    smooth_iterations: 10
}


createModule().then((Module) => {
    let cells = [];

    const generateCave = function (gen) {
        let buff = generator.generate();
        cells = [];
        for (let i = 0; i < buff.size(); i++) {
            cells.push(buff.get(i));

        }

        return cells;
    }

    const drawCave = function () {

        ctx.clearRect(0, 0, canvas.width, canvas.height);
        for (let i = 0; i < cells.length; i++) {

            let x = i % generator.getWidth();
            let y = Math.floor(i / generator.getWidth());

            let val = cells[i];
            color.set(val, val, val);
            // console.log(`x: ${x}, y: ${y}`);
            ctx.fillStyle = color.toHexString();
            ctx.fillRect(x * 5, y * 5, 5, 5);
        }
    }


    generator = new Module.CaveGenerator();
    generator.setThreshold(120);
    generator.setWidth(128);
    generator.setHeight(128);
    generateCave(generator);


    const pane = new Pane({ title: "Generation Parameters" });
    const threshold_input = pane.addInput(PARAMS, 'threshold', { min: 0, max: 255, step: 1 });
    const smooth_iterations_input = pane.addInput(PARAMS, "smooth_iterations", { min: 0, max: 30, step: 1 })
    threshold_input.on("change", (event) => {
        generator.setThreshold(event.value)
        generateCave(generator);
        drawCave();
    })

    smooth_iterations_input.on("change", (event) => {
        generator.setSmoothIterations(event.value)
        generateCave(generator);
        drawCave();
    })

    let canvas: HTMLCanvasElement = document.getElementById("canvas") as HTMLCanvasElement;
    let ctx = canvas.getContext("2d");
    window.addEventListener("resize", () => {
        canvas.width = window.innerWidth;
        canvas.height = window.innerHeight;
        drawCave();
    })
    let resize = new Event("resize");
    window.dispatchEvent(resize);

    let seed = 0;
    canvas.addEventListener("click", () => {

        seed += 10;
        generator.setRandomSeed(seed);
        generateCave(generator);

        drawCave();
    })
});