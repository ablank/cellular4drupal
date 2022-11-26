import imagemin from 'imagemin';
import imageminJpegtran from 'imagemin-jpegtran';
import imageminPngquant from 'imagemin-pngquant';

import { promises as fsPromises } from 'node:fs';
import { promisify } from 'node:util';
import path from 'node:path';
import fs from 'graceful-fs';

const writeFile = promisify(fs.writeFile);

const srcdir = 'src/assets/images';
const distdir = 'dist/assets/images';

imagemin([srcdir + '/**/*.{jpg,jpeg,png}'], {
  plugins: [
    imageminJpegtran({
      progressive: true
    }),
    imageminPngquant({
      speed: 4,
      quality: [0.65, 0.9]
    })
  ]
}).then(files => files
  .forEach(async v => {
    let source = path.parse(v.sourcePath);
    v.destinationPath = `${source.dir.replace(srcdir, distdir)}/${source.name}${source.ext}`;
    await fsPromises.mkdir(path.dirname(v.destinationPath), { recursive: true });
    await writeFile(v.destinationPath, v.data);
  })
);