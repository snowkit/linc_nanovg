
import snow.api.Debug.*;
import snow.types.Types;
import snow.modules.opengl.GL;

import nanovg.Nvg;
using cpp.NativeString;

typedef UserConfig = {}

@:log_as('app')
class Main extends snow.App {
    
    var font:Int;
    var vg:cpp.Pointer<NvgContext>;
    var linearGradient:NvgPaint;

    function new() {}

    override function config( config:AppConfig ) : AppConfig {

        config.window.title = 'linc nanovg example';

            //currently required for GL3.x in linc_nanvog, will add more flags
        config.render.opengl.profile = core;

            //required for nanovg
        config.render.stencil = 8;
        config.render.depth = 24;

        return config;

    } //config

    override function ready() {

        log('ready');

        trace('OpenGL version: ${GL.versionString()}');

        vg = Nvg.createGL(NvgMode.ANTIALIAS);
        font = Nvg.createFont(vg, "arial", "assets/DroidSans.ttf");
        linearGradient = Nvg.linearGradient(vg, 0, 0, 500, 500, Nvg.rgba(255,192,0,255), Nvg.rgba(0,0,0,255));

    } //ready

    override function onkeyup( keycode:Int, _,_, mod:ModState, _,_ ) {

        if( keycode == Key.escape ) {
            app.shutdown();
        }

    } //onkeyup

    override function tick( delta:Float ) {

            //Handling high DPI:
            //- glViewport takes backing renderable size (render_w/_h)
            //- our app wants window sized coordinates (window_w/_h)
            //- snow gives us backing size, we convert for our needs
            //- nanovg takes window size + ratio, easy!

        var dpr = app.runtime.window_device_pixel_ratio();
        var render_w = app.runtime.window_width();
        var render_h = app.runtime.window_height();
        var window_width = Math.floor(render_w/dpr);
        var window_height = Math.floor(render_h/dpr);

        GL.viewport(0, 0, render_w, render_h);
        GL.clearColor (0.3, 0.3, 0.3, 1.0);
        GL.clear(GL.COLOR_BUFFER_BIT | GL.DEPTH_BUFFER_BIT | GL.STENCIL_BUFFER_BIT);

        Nvg.beginFrame(vg, window_width, window_height, dpr);

        Nvg.rect(vg, 100, 100, 500,300);
        Nvg.circle(vg, 120,120, 250);
        Nvg.pathWinding(vg, NvgSolidity.HOLE);   // Mark circle as a hole.
        Nvg.fillPaint(vg, linearGradient);
        Nvg.fill(vg);
        
        Nvg.fontFaceId(vg, font);
        Nvg.fillColor(vg, Nvg.rgba(255,0,0,255));
        Nvg.text(vg, 50, 50, "This is some text", null);

        Nvg.fontSize(vg, 100.0);
        Nvg.fontFaceId(vg, font);
        Nvg.fillColor(vg, Nvg.rgba(255,255,255,64));
        Nvg.textAlign(vg, NvgAlign.ALIGN_LEFT|NvgAlign.ALIGN_MIDDLE);
        Nvg.text(vg, 100, 100, "Some other text!", null);

        Nvg.endFrame(vg);

    } //update

} //Main
