const fastify = require("fastify");

const boot = async () => {
  const app = fastify({ logger: true });

  app.get("/hello", async (request, reply) => {
    return { hello: "world" };
  });

  app.post("/ping", async (request, reply) => {
    const pong = request.body.message;
    return { pong: "Received: " + pong };
  });

  await app.listen({ port: 3000, host: "0.0.0.0" });
};

boot();
