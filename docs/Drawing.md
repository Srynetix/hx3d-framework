Three ways to draw
------------------

You can draw with three different techniques.

First way: Batch, the easy way
-----------------------

The Batch is a "common" batch which draw every mesh or sprite when you call
the draw() method.

It can draw meshes, sprites and texts.
You can even draw texts with a math function to spice things a little.

```
Batch batch;
batch.setShader(shader);
batch.setCamera(camera);

batch.draw(mesh);
batch.draw(sprite);
batch.draw(text);
batch.draw(text, math::Function(
  Core::App()->getElapsedTime() * 2.f,
  0.5f,
  [](float& x, float& y, float y) {
    y = std::sin(t) * 10.f;
}));
```

Second way: SpriteBatch, for super speed sprite drawing
-------------------------------------------------------

The SpriteBatch is specialized for sprite drawing.
It can be twice as fast as the normal Batch, but only for sprites.

```
SpriteBatch batch;

batch.setShader(shader);
batch.setCamera(camera);
batch.draw(sprite);
```

Third way: No batches, the hard way
-----------------------------------

Activate a shader, pass it your matrices, and draw your meshes without batches.
Not really practical, but you can customize if you want.

```
Shader::use(shader);
shader->setUniformMatrix4f("u_modelview", modelview);

sprite.draw(shader);
Shader::disable();
```
