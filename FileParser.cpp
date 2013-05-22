#include "FileParser.h"

bool FileParser::parse(const char* filename, Camera *camera, rgb *background,
		rgb *ambientLight, vector<Shape*> *shapes, vector<Light*> *lights) {

	FILE *fp = fopen(filename, "r");
	if (!fp) {
		cout << "FileParser: unable to open file: " << filename << endl;
		return false;
	}

	Material curMat;
	ImageTexture curTex;
	char line[256], buf[100];
	float temp1, temp2, temp3;
	float t[9];
	while (!feof(fp)) {
		line[0] = NULL;
		fscanf(fp, "%s", line);


		if (!strcmp(line, "background")) {
			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			background->_r = temp1;
			background->_g = temp2;
			background->_b = temp3;
		} else if (!strcmp(line, "#")) {
			fgets(buf, 100, fp);
		}

		else if (!strcmp(line, "material")) {
			fscanf(fp, "%f %f %f %f %f %f %f %f %f", &t[0], &t[1], &t[2],
					&t[3], &t[4], &t[5], &t[6], &t[7], &t[8]);
			rgb r(t[0], t[1], t[2]);
			curMat.color = r;
			curMat.ka = t[3];
			curMat.kd = t[4];
			curMat.ks = t[5];
			curMat.n_s = t[6];
			curMat.t = t[7];
			curMat.refract = t[8];
			curMat.isTexed = false;
			curMat.bumpMap = false;
		} else if (!strcmp(line, "sphere")) {
			fscanf(fp, "%f %f %f %f", &t[0], &t[1], &t[2], &t[3]);

			Vector3 v(t[0], t[1], t[2]);
			Sphere *s = new Sphere(v, t[3], curMat);
			shapes->push_back(s);
		} else if (!strcmp(line, "tsphere")) {
			fscanf(fp, "%f %f %f %f", &t[0], &t[1], &t[2], &t[3]);

			Vector3 v(t[0], t[1], t[2]);
			Sphere *s = new Sphere(v, t[3], curMat);
			shapes->push_back(s);
		} else if (!strcmp(line, "dynsphere")) {
			fscanf(fp, "%f %f %f %f", &t[0], &t[1], &t[2], &t[3], &t[4], &t[5]);

			Vector3 v(t[0], t[1], t[2]);
			DynSphere *s = new DynSphere(v, t[3], curMat, t[4], t[5]);
			shapes->push_back(s);
		} else if (!strcmp(line, "ambient_light")) {
			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			ambientLight->_r = temp1;
			ambientLight->_g = temp2;
			ambientLight->_b = temp3;
		}

		//camera

		else if (!strcmp(line, "camera_from")) {

			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			camera->from = Vector3(temp1, temp2, temp3);

		}

		else if (!strcmp(line, "camera_up")) {

			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			camera->up = Vector3(temp1, temp2, temp3);
		} else if (!strcmp(line, "camera_target")) {
			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			camera->target = Vector3(temp1, temp2, temp3);
		}

		else if (!strcmp(line, "camera_forw")) {

			fscanf(fp, "%f %f %f", &temp1, &temp2, &temp3);
			camera->forw = Vector3(temp1, temp2, temp3);
		} else if (!strcmp(line, "camera_angle")) {
			fscanf(fp, "%f", &temp1);
			camera->angleX = temp1;
		} else if (!strcmp(line, "camera_resolution")) {
			fscanf(fp, "%f %f", &temp1, &temp2);
			camera->resX = temp1;
			camera->resY = temp2;
		} else if (!strcmp(line, "render")) {
			fscanf(fp, "%s", outfile);
		} else if (!strcmp(line, "mesh")) {
			char tmp[50];
			fscanf(fp, "%s", tmp);
			mesh temp(tmp);
			for (int i = 0; i < temp.fTotal; i++) {

				Vector3 p0 = vec3Convert(temp.vList[temp.faceList[i][0].v]);
				Vector3 p1 = vec3Convert(temp.vList[temp.faceList[i][1].v]);
				Vector3 p2 = vec3Convert(temp.vList[temp.faceList[i][2].v]);
				Vector3 vt0 = vec3Convert(temp.tList[temp.faceList[i][0].t]);
				Vector3 vt1 = vec3Convert(temp.tList[temp.faceList[i][1].t]);
				Vector3 vt2 = vec3Convert(temp.tList[temp.faceList[i][2].t]);
				Triangle *t = new Triangle(p0, p1, p2, curMat, vt0, vt1, vt2);

				shapes->push_back(t);
			}
		} else if (!strcmp(line, "point_light")) {
			fscanf(fp, "%f %f %f %f %f %f", &t[0], &t[1], &t[2], &t[3], &t[4],
					&t[5]);
			Pointlight *p = new Pointlight();
			p->light.setRed(t[0]);
			p->light.setGreen(t[1]);
			p->light.setBlue(t[2]);
			p->location.setX(t[3]);
			p->location.setY(t[4]);
			p->location.setZ(t[5]);
			lights->push_back(p);
		} else if (!strcmp(line, "area_light")) {
			fscanf(fp, "%f %f %f %f %f %f %f ", &t[0], &t[1], &t[2], &t[3],
					&t[4], &t[5], &t[6]);
			rgb color(t[0], t[1], t[2]);
			Vector3 loc(t[3], t[4], t[5]);
			AreaLight *a = new AreaLight(loc,(double)t[6], color);
			lights->push_back(a);
		} else if (!strcmp(line, "parallel_light")) {
			fscanf(fp, "%f %f %f %f %f %f", &t[0], &t[1], &t[2], &t[3], &t[4],
					&t[5]);
			DirectionalLight *p = new DirectionalLight();
			p->light.setRed(t[0]);
			p->light.setGreen(t[1]);
			p->light.setBlue(t[2]);
			p->location.setX(t[3]);
			p->location.setY(t[4]);
			p->location.setZ(t[5]);
			lights->push_back(p);
		} else if (!strcmp(line, "trace_depth")) {
			fscanf(fp, "%f", &t[0]);
			depth = t[0];
		} else if (!strcmp(line, "texture")) {

			char tmp[50];
			fscanf(fp, "%s", tmp);
			curMat.tex = new ImageTexture(tmp);
			curMat.isTexed = true;
		} else if (!strcmp(line, "bumpMap")) {
			char tmp1[50], tmp2[50];
			fscanf(fp, "%s", tmp1);
			fscanf(fp, "%s", tmp2);
			curMat.tex = new BumpMapping(tmp1, tmp2);
			curMat.isTexed = true;
			curMat.bumpMap = true;
		} else if (!strcmp(line, "jitter")) {
			int t1, t2;
			fscanf(fp, "%d %d", &t1, &t2);
			camera->jitter[0] = t1;
			camera->jitter[1] = t2;

		}
	}

	fclose(fp);
	return true;
}
